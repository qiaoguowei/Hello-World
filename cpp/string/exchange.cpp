#include <iostream>
#include <string>

int main()
{
    std::string m_user = "test1";
    std::string m_domain = "skyguard";
    std::string temp_mail = "test1@skyguard.com.cn";

    if (m_user.find('@') == std::string::npos
            && temp_mail.find(m_domain) != std::string::npos
            && temp_mail.find('@') != std::string::npos)
    {
        temp_mail = temp_mail.substr(0, temp_mail.find('@'));
    }

    std::cout << temp_mail << std::endl;
}
