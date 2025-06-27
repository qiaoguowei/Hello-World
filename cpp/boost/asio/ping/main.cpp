#include <iostream>
#include "icmp_header.hpp"
#include "ipv4_header.hpp"
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/system/error_code.hpp>
#include <list>
#include <string>

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
