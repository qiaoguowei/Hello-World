#! /bin/bash

g++ $1 -I/home/qgw/SDK/boost_1_73_0 -L/home/qgw/SDK/boost_1_73_0/stage/lib -lrt -pthread -lboost_filesystem
