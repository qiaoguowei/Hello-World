#!/bin/bash

g++ $1 -I/usr/include -L/usr/lib/x86_64-linux-gnu  -lcrypto -lssl
