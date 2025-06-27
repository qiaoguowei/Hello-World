#!/bin/bash

g++ $1 -I/home/qgw/SDK/boost_1_73_0 -L/usr/lib/x86_64-linux-gnu -L/home/qgw/SDK/boost_1_73_0/stage/lib -ljsoncpp -lboost_filesystem
