#include <iostream>
#include <string>

int main()
{
    std::string name = "@aaaaa/bbbbb";
    std::string::size_type n = name.find('/');
    std::cout << name.size() - n - 1 << std::endl;
    name = name.substr(name.find('/') + 1, name.size() - name.find('/') - 1);
    std::cout << n << std::endl;
    std::cout << name << std::endl;
    std::cout << "====================================" << std::endl;

    std::string fqdn = "@skyguard.com\\qgw";
    fqdn = fqdn.substr(1, fqdn.size() - 1);
    std::cout << fqdn << std::endl;

    std::string get_fqdn = "skyguard.com";

    std::cout << fqdn.compare(0, get_fqdn.size(), get_fqdn) << std::endl;
}

