#include <iostream>
#include <string>
#include <unistd.h>
#include <boost/scope_exit.hpp>
#include <sys/types.h>
#include <pwd.h>

using namespace std;

/* 
 * int getpwnam_r(const char *name, struct passwd *pwd,
 *                char *buf, size_t buflen, struct passwd **result);
 * 将检索到的passwd结构存储在pwd指向的空间中
 * 由passwd结构成员指向的字符串字段存储在大小为buflen的buffer buf中。
 * 指向结果的指针(在成功的情况下)或NULL(在没有找到条目或发生错误的情况下)存储在*result中。
 *
 * On  success,  getpwnam_r()  and  getpwuid_r()  return  zero, and set *result to pwd
 * If no matching password record was found, these functions return 0 and store NULL in *result.
 * In case of error, an error  number  is returned, and NULL is stored in *result.
 * */

bool getPosixHome(const std::string& userName, std::string& homeDir)
{
    size_t bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);
    if (bufsize == -1)
    {
        bufsize = 16384;
    }
    cout << "bufsize : " << bufsize << endl;

    char *buf = static_cast<char *>(malloc(bufsize));
    if (buf == NULL)
    {
        cout << "cannot alloc memory." << endl;
        return false;
    }
    BOOST_SCOPE_EXIT(&buf)
    {
        free(buf);
    }BOOST_SCOPE_EXIT_END

    struct passwd pwd;
    struct passwd *result;
    int s = getpwnam_r(userName.c_str(), &pwd, buf, bufsize, &result);
    if (result == NULL)
    {
        if (s == 0)
        {
            cout << "not found user." << userName << "'s home dir." << endl;
        }
        else
        {
            cout << "error." << s << " in found user." << userName << endl;
        }
        return false;
    }
    homeDir = pwd.pw_dir;
    cout << buf << endl;
    cout << "pw_name: "   << pwd.pw_name   << endl;
    cout << "pw_passwd: " << pwd.pw_passwd << endl;
    cout << "pw_uid: "    << pwd.pw_uid    << endl;
    cout << "pw_gid: "    << pwd.pw_gid    << endl;
    cout << "pw_gecos: "  << pwd.pw_gecos  << endl;
    cout << "pw_dir: "    << pwd.pw_dir    << endl;
    cout << "pw_shell: "  << pwd.pw_shell  << endl;
    return true;
}

int main()
{
    string userName = "qgw";
    string homeDir;
    getPosixHome(userName, homeDir);
    cout << homeDir << endl;
}

















