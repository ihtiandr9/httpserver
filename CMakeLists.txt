cmake_minimum_required(VERSION 3.5...3.11)
project(httpserver)
    add_executable(httpserver
        src/server.cpp)
    include_directories(third_party/cpp-httplib)
    target_link_libraries(httpserver pthread)
    add_definitions(-pthread -ggdb -O0)
