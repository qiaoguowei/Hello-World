#include <iostream>
#include <string>

int main()
{
    std::string path = "C:/Users\\qiaoguowei\\Desktop\\TeSaoCeShi\\UCSCLite_3.15.0-426-win-x86_64\\ucsc_sdk\\template/6c52201a-166c-4f2e-bbae-5effbc16d9e5_50/Script_GDPR_Malaysia_ID_Without_Date_Validation_With_Terms_Matcher/Script_GDPR_Malaysia_ID_Without_Date_Validation_With_Terms_Matcher.pm.enc";

    std::cout << path << std::endl;
    for (auto& c : path)
    {
        if (c == '/')
            c = '\\';
    }

    std::cout << path << std::endl;
    std::cout << path.size() << std::endl;
}
