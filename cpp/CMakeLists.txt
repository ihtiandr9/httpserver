cmake_minimum_required(VERSION 3.5...3.11)
project(httpserver)
# Common options
    include_directories(third_party/cpp-httplib)
    add_definitions(-pthread -ggdb -O0 -static)
    set(LIBS pthread)
    if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
        set(LIBS ${LIBS} pthread -static)
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "FreeBSD")
        set(LIBS ${LIBS} pthread -static)
    else()
        set(LIBS ${LIBS} pthread ws2_32 -static)
    endif()
    message(NOTICE ${CMAKE_SYSTEM_NAME})
# http server target
    add_executable(httpserver
        src/server.cpp)
    target_link_libraries(httpserver ${LIBS})
# http client target
    add_executable(httpclient
        src/client.cpp)
    target_link_libraries(httpclient ${LIBS})
