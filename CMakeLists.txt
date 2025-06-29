cmake_minimum_required(VERSION 3.5...3.11)
project(httpserver)
# Common options
    include_directories(third_party/cpp-httplib)
    add_definitions(-pthread -ggdb -O0)
# http server target
    add_executable(httpserver
        src/server.cpp)
    target_link_libraries(httpserver pthread)
# http client target
    add_executable(httpclient
        src/client.cpp)
    target_link_libraries(httpclient pthread)
