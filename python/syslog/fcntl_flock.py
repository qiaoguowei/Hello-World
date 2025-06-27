# -*- coding:utf-8 -*-

import fcntl
import time

def tryLock(fd):
    try:
        fcntl.flock(fd, fcntl.LOCK_EX | fcntl.LOCK_NB)
        return True
    except Exception as e:
        print("flock() failed.")
        return False

def tryUnLock(fd):
    try:
        fcntl.flock(fd, fcntl.LOCK_UN)
        return True
    except Exception as e:
        print("unlock failed.")
        return False

if __name__ == "__main__":
    fd = open("./locked_file.txt", "w+")
    if tryLock(fd) == True:
        print("try lock success.")
        time.sleep(10)
        tryUnLock(fd)
