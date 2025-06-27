cmake_minimum_required(VERSION 3.1)

project(test_sqlite3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall ")

#link_directories(/home/qgw/lib)
include_directories(/usr/include)

#set(cxx_source ./sqlite3_get_table.cpp)
file(GLOB cxx_source "./SqliteConnection.cpp" "./RecordSet.cpp")
file(GLOB hpp_source "./SqliteConnection.h" "./RecordSet.h")

#add_executable(mysqlite3 ${cxx_source})
add_library(mysqlite3 SHARED ${cxx_source} ${hpp_source})
#target_link_libraries(exec sqlite3)
#target_link_libraries(mysqlite3 /home/qgw/lib/libsqlite3.so)
target_link_libraries(mysqlite3 /usr/lib/x86_64-linux-gnu/libsqlite3.so)

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}")
message("CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
#install(FILES exec DESTINATION /home/qgw/my_github/Hello-World/cpp/boost/filesystem/bin)
#install(TARGETS exec RUNTIME DESTINATION bin)
#target_link_libraries(cxx_source boost_filesystem)
#TARGET_LINK_LIBRARIES(exec boost_filesystem)
