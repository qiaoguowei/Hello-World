#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>

int main()
{
    std::string sql = "(submitter_name and submitter_ip and submitter_email and submitter_fqdn and )";
    std::cout << sql << std::endl;
    boost::algorithm::replace_last(sql, " and ", "");

    std::cout << sql << std::endl;
}
