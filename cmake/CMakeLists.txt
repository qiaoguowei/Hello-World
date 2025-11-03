
#CMake 最低版本号要求
cmake_minimum_required(VERSION 3.18)

#工程，他不是执行文件名
PROJECT(Darren)

#手动加入文件 ${变量名}
SET(SRC_LIST main.c)
SET(SRC_LIST2 main2.c)

#message和echo类似
#cmake命令执行的目录
MESSAGE(STATUS "THIS IS PROJECT_BINARY_DIR DIR" ${PROJECT_BINARY_DIR})
#用于表示当前 CMake 项目的根目录路径（即包含 CMakeLists.txt 文件且通过 project() 命令定义项目的目录）。
MESSAGE(STATUS "THIS IS PROJECT_SOURCE_DIR DIR" ${PROJECT_SOURCE_DIR})
#CMakeLists.txt所在的目录
MESSAGE(STATUS "THIS IS CMAKE_CURRENT_SOURCE_DIR DIR" ${CMAKE_CURRENT_SOUCE_DIR})

ADD_EXECUTABLE(xxx ${SRC_LIST})
ADD_EXECUTABLE(xxx2 ${SRC_LIST2})

#添加子目录
ADD_SUBDIRECTORY(src)
#找头文件
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOUCE_DIR}/dir1")
# 相对路径的方式
INCLUDE_DIRECTORIES("dir1")
#生成库文件
ADD_LIBRARY(hello_shared SHARED SRC_LIST)
ADD_LIBRARY(hello_static STATIC SRC_LIST)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/debug)

TARGET_LINK_LIBRARIES(hello_shared ssl thrift)

#
INSTALL(TARGET xxx RUNTIME DESTINATION bin)
#                源目录             目标目录   -DCMAKE_INSTALL_PREFIX=
INSTALL(DIRECTORY doc/ DESTINATION shared/doc/cmake/0voice)

# 将当前目录下的源码添加到DIR_SRCS
AUX_SOURCE_DIRECTORY(. DIR_SRCS)












