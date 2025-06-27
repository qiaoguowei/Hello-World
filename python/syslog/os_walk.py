import os

path = "/opt/skyguard/ucs/var/log"

for root, dirs, files in os.walk(path):
    print("root:", root)
    print("dirs:", dirs)
    print("files:", files)
