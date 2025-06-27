#!/usr/bin/env python3

import sys
import os
import getopt
import json

##sys.path.append("/opt/skyguard/ucs/lib/python2.7/site-packages")

def main(argv):
    try:
        opts, args = getopt.getopt(argv[1:], "f", ["file_name="])
    except getopt.GetoptError as err:
        print(str(err))
    myfilename = ""
    for key, value in opts:
        if key in ("-f", "--file_name"):
            myfilename = "tttt"

    if len(myfilename) == 0:
        print("myfilename is null.")
        return

    if os.path.exists(myfilename):
        fd = open(myfilename, "r")
        js = json.loads(fd.read())
        json_string = json.dumps(js, ensure_ascii=False, indent=4).encode('utf8')

        wfd = open("./json_result.json", "wb")
        wfd.write(json_string)
        wfd.close()
        fd.close()
    else:
        print(myfilename + " is not exists.")
        return


if __name__ == "__main__":
    main(sys.argv)


