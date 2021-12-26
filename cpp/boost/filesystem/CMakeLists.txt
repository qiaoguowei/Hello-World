cmake_minimum_required(VERSION 3.1)

project(test_filesystem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall ")

link_directories(/usr/lib/x86_64-linux-gnu)
include_directories(/usr/include/boost)

set(cxx_source ./path.cpp)

add_executable(exec ${cxx_source})
#target_link_libraries(cxx_source boost_filesystem)
TARGET_LINK_LIBRARIES(exec boost_filesystem)
