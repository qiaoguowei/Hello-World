#include "NetworkUtility.h"
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include "./asio_icmp/icmp_header.hpp"
#include "./asio_icmp/ipv4_header.hpp"
#include "skyguard/ucsc_sdk/EnumToString.h"

UCSCSDK_BEGIN

class TryConnect
{
public:
    TryConnect();

public:
    std::string get_connect_address(
        const std::string& ip, 
        uint16_t port,
        uint32_t timeout);

private:
    void check_dealine();

private:
    boost::asio::io_service ios_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::deadline_timer deadline_;
};

TryConnect::TryConnect()
        : socket_(ios_)
        , deadline_(ios_)
{
    check_dealine();
}

std::string TryConnect::get_connect_address(
    const std::string& ip,
    uint16_t port, 
    uint32_t timeout
    )
{
    std::string local_addr;

    try
    {
        boost::asio::ip::tcp::resolver::query query_(ip, std::to_string(port));
        boost::asio::ip::tcp::resolver::iterator iter_ = boost::asio::ip::tcp::resolver(ios_).resolve(query_);
        boost::system::error_code ec_ = boost::asio::error::would_block;

        deadline_.expires_from_now(boost::posix_time::seconds(timeout));
        boost::asio::async_connect(socket_, iter_, boost::lambda::var(ec_) = boost::lambda::_1);

        do {
            ios_.run_one();
        } while (ec_ == boost::asio::error::would_block);

        if (socket_.is_open())
        {
            local_addr = socket_.local_endpoint().address().to_string();
        }
    }
    catch (std::exception& e)
    {
        SGT_ERROR("tryConnect", "get connect address failed, ip : " << ip << ", port : " << port << ", exception:" << e.what() << ".");
    }

    return local_addr;
}

void TryConnect::check_dealine()
{
    if (deadline_.expires_at() <= boost::asio::deadline_timer::traits_type::now())
    {
        boost::system::error_code ignored_ec;
        socket_.close(ignored_ec);

        deadline_.expires_at(boost::posix_time::pos_infin);

        SGT_DEBUG("tryConnect", "time out.");
    }

    deadline_.async_wait(boost::bind(&TryConnect::check_dealine, this));
}

///

class ICMPClient
{
public:
    ICMPClient()
        : timer_(io_), sequence_number_(0), num_replies_(0)
    {
    }

    bool ping(const std::string& ip, uint32_t timeout)
    {
        try
        {
            boost::asio::streambuf reply_buffer_;
            boost::asio::deadline_timer timer_(io_);
            boost::asio::ip::icmp::resolver resolver_(io_);
            boost::asio::ip::icmp::socket socket_(io_, boost::asio::ip::icmp::v4());
            boost::asio::ip::icmp::resolver::query query(boost::asio::ip::icmp::v4(), ip, "");
            boost::asio::ip::icmp::endpoint destination_ = *resolver_.resolve(query);

            num_replies_ = 0;
            sequence_number_ = 0;
            start_send(socket_, destination_, ip, timer_, timeout);
            start_receive(socket_, timer_, reply_buffer_);

            io_.reset();
            io_.run();
        }
        catch (const boost::system::system_error& e)
        {
            SGT_INFO("ICMPClient", "failed to ping, ip = " << ip << " , boost system error = " << e.code().value() << " .");
        }
        catch (const std::exception& e)
        {
            SGT_INFO("ICMPClient", "failed to ping, ip = " << ip << " , std exception = " << e.what() << " .");
        }

        return (num_replies_ > 0);
    }

private:
    void start_send(
        boost::asio::ip::icmp::socket& socket_,
        boost::asio::ip::icmp::endpoint& destination_,
        const std::string& ip,
        boost::asio::deadline_timer& time_,
        uint32_t timeout)
    {
        std::string body("\"Hello!\" from Asio ping.");

        // Create an ICMP header for an echo request.
        icmp_header echo_request;
        echo_request.type(icmp_header::echo_request);
        echo_request.code(0);
        echo_request.identifier(get_identifier());
        echo_request.sequence_number(++sequence_number_);
        compute_checksum(echo_request, body.begin(), body.end());

        // Encode the request packet.
        boost::asio::streambuf request_buffer;
        std::ostream os(&request_buffer);
        os << echo_request << body;

        // Send the request.
        boost::posix_time::ptime time_sent_ = boost::posix_time::microsec_clock::universal_time();
        socket_.send_to(request_buffer.data(), destination_);

        // Wait up to five seconds for a reply.
        num_replies_ = 0;
        timer_.expires_at(time_sent_ + boost::posix_time::seconds(timeout));
        timer_.async_wait(boost::bind(&ICMPClient::handle_timeout, this, 
            boost::asio::placeholders::error, boost::ref(ip)));
    }

    void handle_timeout(const boost::system::error_code& ec, const std::string& ip)
    {
        SGT_DEBUG("ICMPClient", "handle_timeout, ip = " << ip <<
            ", isTimeout = " << BoolToString(num_replies_ == 0) <<
            ", errorCode = " << ec.value() <<
            ", [boost::asio::error::timed_out =  " << boost::asio::error::timed_out <<
            ", boost::asio::error::operation_aborted = " << boost::asio::error::operation_aborted <<
            "] .");
        io_.stop();
    }

    void start_receive(
        boost::asio::ip::icmp::socket& socket_,
        boost::asio::deadline_timer& time_,
        boost::asio::streambuf& reply_buffer_)
    {
        // Discard any data already in the buffer.
        reply_buffer_.consume(reply_buffer_.size());

        // Wait for a reply. We prepare the buffer to receive up to 64KB.
        socket_.async_receive(reply_buffer_.prepare(65536),
            boost::bind(&ICMPClient::handle_receive, this, boost::ref(time_), boost::ref(reply_buffer_), 
                boost::asio::placeholders::error, _2));
    }

    void handle_receive(
        boost::asio::deadline_timer& time_,
        boost::asio::streambuf& reply_buffer_,
        const boost::system::error_code& ec,
        std::size_t length)
    {
        SGT_DEBUG("ICMPClient", "handle_receive, errorCode = " << ec.value() <<
            ", length = " << length << ".");

        if (!ec)
        {
            // The actual number of bytes received is committed to the buffer so that we
            // can extract it using a std::istream object.
            reply_buffer_.commit(length);

            // Decode the reply packet.
            std::istream is(&reply_buffer_);
            ipv4_header ipv4_hdr;
            icmp_header icmp_hdr;
            is >> ipv4_hdr >> icmp_hdr;

            // We can receive all ICMP packets received by the host, so we need to
            // filter out only the echo replies that match the our identifier and
            // expected sequence number.
            if (is && icmp_hdr.type() == icmp_header::echo_reply
                && icmp_hdr.identifier() == get_identifier()
                && icmp_hdr.sequence_number() == sequence_number_)
            {
                // If this is the first reply, interrupt the five second timeout.
                num_replies_++;
            }
        }

        timer_.cancel();
    }

    static unsigned short get_identifier()
    {
#if defined(BOOST_ASIO_WINDOWS)
        return static_cast<unsigned short>(::GetCurrentProcessId());
#else
        return static_cast<unsigned short>(::getpid());
#endif
    }

    boost::asio::io_service io_;
    boost::asio::deadline_timer timer_;
    uint16_t sequence_number_;
    std::size_t num_replies_;
};


///

bool NetworkUtility::getLocalIp(
    const std::string& host, 
    uint16_t port,
    uint32_t timeout, 
    std::string& local_ip
    )
{
    TryConnect connect_;
    local_ip = connect_.get_connect_address(host, port, timeout);
    if (local_ip == "0.0.0.0")
        local_ip.clear();

    return !local_ip.empty();
}

bool NetworkUtility::updateNICIp(
    const std::string& host, 
    uint16_t port,
    uint32_t timeout, 
    std::vector<NetworkCard>& nics
    )
{
    if (nics.empty())
    {
        SGT_WARN("NetworkUtility", "nics is empty.");
        return false;
    }

    // try connect 8836 port
    std::string local_ip;
    if (!getLocalIp(host, port, timeout, local_ip))
    {
        SGT_WARN("NetworkUtility", "failed to get local connect ip address, ip : " << host << ", port : " << port);
        return false;
    }
    else
    {
        bool ipv4_found = false;
        for (auto nic_iter = nics.begin(); nic_iter != nics.end(); ++nic_iter)
        {
            for (auto ipv4_iter = nic_iter->ipv4s.begin(); ipv4_iter != nic_iter->ipv4s.end(); ++ipv4_iter)
            {
                if (*ipv4_iter == local_ip)
                {
                    if (ipv4_iter != nic_iter->ipv4s.begin())
                    {
                        std::string swap_value = nic_iter->ipv4s.front();
                        *nic_iter->ipv4s.begin() = local_ip;
                        *ipv4_iter = swap_value;
                    }

                    ipv4_found = true;
                    break;
                }
            }

            if (ipv4_found)
            {
                if (nic_iter != nics.begin())
                {
                    auto swap_value = nics.front();
                    *nics.begin() = *nic_iter;
                    *nic_iter = swap_value;
                }
                break;
            }
        }

        if (!ipv4_found)
        {
            auto& ipv4s = nics.front().ipv4s;
            ipv4s.insert(ipv4s.begin(), local_ip);

            SGT_WARN("NetworkUtility", "not find the ip address, insert to :" << local_ip << " .");
        }

        return true;
    }
}

std::list<std::string> NetworkUtility::resolve_ip(
    const std::string& domain
    )
{
    std::list<std::string> ips;

    try
    {
        boost::asio::io_service ios;
        boost::asio::ip::tcp::resolver slv(ios);
        boost::asio::ip::tcp::resolver::query qry(domain, "");
        boost::asio::ip::tcp::resolver::iterator iter = slv.resolve(qry);
        boost::asio::ip::tcp::resolver::iterator iend;

        for (; iter != iend; iter++)
        {
            ips.push_back((*iter).endpoint().address().to_string());
        }
    }
    catch (std::exception& e)
    {
        SGT_ERROR("NetworkUtility", "resolve_ip failed, domain : <" << domain << ">, exception:" << e.what() << ".");
    }

    SGT_DEBUG("ICMPClient", "resolve_ip, domain = " << domain <<
         ", ips = " << boost::join(ips, " ") << ".");

    return ips;
}

bool NetworkUtility::ping_ip(
    const std::list<std::string>& ips,
    uint32_t timeout
    )
{
    bool r = false;
    for (const auto& ip : ips)
    {
        ICMPClient c_;
        r = c_.ping(ip, timeout);
        SGT_DEBUG("NetworkUtility", (r ? "successfully to " : "failed to ") << "ping, ip = " << ip << " .");
        if (r)
            break;
    }

    return r;
}

bool NetworkUtility::ping_ip(
    const std::string &ip,
    uint32_t timeout
)
{
    bool r = false;
    ICMPClient c_;

    r = c_.ping(ip, timeout);
    SGT_DEBUG("NetworkUtility", (r ? "successfully to " : "failed to ") << "ping, ip = " << ip << " .");

    return r;
}

bool NetworkUtility::is_valid_ipv4_address(
    const std::string& address
    )
{
    try {
        boost::asio::ip::address ipv4Addr = boost::asio::ip::address::from_string(address);
        return (ipv4Addr.is_v4() == true);
    }
    catch (std::exception& e)
    {
        SGT_INFO("NetworkUtility", "is_valid_ipv4_address failed, address : <" << address << ">, exception:" << e.what() << ".");
    }

    return false;
}

std::string NetworkUtility::host_to_ip(
    const std::string& host
    )
{
    if (NetworkUtility::is_valid_ipv4_address(host))
        return host;

    std::list<std::string> ip_list(NetworkUtility::resolve_ip(host));
    if (ip_list.empty())
        return host;

    return (*ip_list.begin());
}

bool NetworkUtility::is_ipv4(const std::string &ip)
{
    if (ip.empty())
        return false;

    try
    {

        boost::asio::ip::address result = boost::asio::ip::address::address::from_string(ip);
        return result.is_v4();
    }
    catch (boost::system::system_error &e)
    {
        SGT_DEBUG("NetworkUtility::is_ipv4 ", ip << "--" << e.what());
        return false;
    }
}

bool NetworkUtility::is_ipv6(const std::string &ip)
{
    if (ip.empty())
        return false;

    try
    {
        
        boost::asio::ip::address result = boost::asio::ip::address::address::from_string(ip);
        return result.is_v6();
    }
    catch (boost::system::system_error &e)
    {
        SGT_DEBUG("NetworkUtility::is_ipv6 ", ip << "--" << e.what());
        return false;
    }
}
UCSCSDK_END

