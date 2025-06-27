#ifndef _QGW_MY_LOCK_H
#define _QGW_MY_LOCK_H

#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void my_lock(int fd)
{
    struct flock lock;

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        std::cout << "fcntl() error: " << strerror(errno) << std::endl;
        return;
    }
}

void my_unlock(int fd)
{
    struct flock lock;

    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    if (fcntl(fd, F_SETLK, &lock) == -1)
    {
        std::cout << "fcntl() error: " << strerror(errno) << std::endl;
        return;
    }
}

#define read_lock(fd, offset, whence, len) \
                lock_reg(fd, F_SETCK, F_RDLCK, offset, whence, len)
#define readw_lock(fd, oofset, whence, len) \
                lock_reg(fd, F_SETCKW, F_RDLCK, offset, whence, len)
#define write_lock(fd, offset, whence, len) \
                lock_reg(fd, F_SETCK, F_WRLCK, offset, whence, len)
#define writew_lock(fd, offset, whence, len) \
                lock_reg(fd, F_SETCKW, F_WRLCK, offset, whence, len)
#define un_lock(fd, offset, whence, len) \
                lock_reg(fd, F_SETCK, F_UNLCK, offset, whence, len)
#define is_read_lockable(fd, offset, whence, len) \
                !lock_test(fd, F_RDLCK, offset, whence, len)
#define is_write_lockable(fd, offset, whence, len) \
                !lock_test(fd, F_WRLCK, offset, whence, len)

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
    struct flock lock;

    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    return (fcntl(fd, cmd, &lock));
}

ptd_t lock_test(int fd, int type, off_t offset, int whence, off_t len)
{
    struct flock lock;

    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    if (fcntl(fd, F_GETLK, &lock) == -1)
    {
        return -1;
    }

    if (lock.l_type == F_UNLCK)
        return 0;

    return lock.l_pid;
}


#endif
