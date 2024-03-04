#ifndef QGW_SFTP_H
#define QGW_SFTP_H

class SftpClient
{
public:
    SftpClient();
    bool openConnectByIp(const string& ip, uint16_t port);

private:
    LIBSSH2_SESSION*        session;
    LIBSSH2_SFTP*           sftp_session;
    LIBSSH2_SFTP_HANDLE*    sftp_handle;
    char                    curdir[2048];
    int                     sockfd;
};



#endif //QGW_SFTP_H
