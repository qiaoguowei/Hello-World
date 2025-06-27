#include <iostream>
#include <string>

using namespace std;

void mkdirp(const string& pathname)
{
    char pwd[NAME_MAX + 1];
    string path(pathname);
    string::size_type pos;

    auto get_prefix = [&path, &pos]() -> string {
        pos = path.find("/");
        string prefix_path = path.substr(0, pos);
        while (path[pos + 1] == '/')
            ++pos;
        return prefix_path;
    };

    ::getcwd(pwd, NAME_MAX);

    if (!path.empty())
    {
        if (path[path.size() - 1] != '/')
            path += "/";

        string prefix_path = get_prefix();
        if (prefix_path.empty())
            prefix_path = "/";

        if (prefix_path == ".")
        {
            path = path.substr(pos + 1);
            mkdirp(path);
            return ;
        }
        else if (prefix_path != "/" && prefix_path != "..")
        {
            if (access(prefix_path.c_str(), F_OK) == -1)
                mkdir(prefix_path.c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
        }

        chdir(prefix_path.c_str());
        path = path.substr(pos + 1);
        mkdirp(path);
        chdir(pwd);
    }
}

int main(int argc, char *argv[])
{

}




















