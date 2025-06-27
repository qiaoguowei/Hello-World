#include <iostream>
#include <curl/curl.h>

int main()
{
    CURL* curl = curl_easy_init();

    std::string uri("Mark8ProjectTeam");
    std::string site_url_or_name = uri;
    std::string encoded_site_path = curl_easy_escape(curl, site_url_or_name.c_str(), site_url_or_name.length());

    std::cout << encoded_site_path << std::endl;
    curl_easy_cleanup(curl);
}
