#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

extern char **environ;

int main()
{
    std::vector<std::string> m_env_vec;
    for (int i = 0; environ[i]; ++i)
    {
        std::cout << environ[i] << std::endl;
        m_env_vec.push_back(std::string(environ[i]));
    }

    char *m_env[100] = {};
    for (int i = 0; i < m_env_vec.size() && i < 100; ++i)
    {
        if (m_env_vec[i].substr(0, 4) == "LANG")
        {
            m_env_vec[i] = "LANG=zh_CN.UTF-8";
        }
        m_env[i] = const_cast<char *>(m_env_vec[i].c_str());
    }
    std::cout << "==========================================" << std::endl;
    for (int i = 0; m_env[i]; ++i)
    {
        std::cout << m_env[i] << std::endl;
        std::cout << i << std::endl;
    }
}
