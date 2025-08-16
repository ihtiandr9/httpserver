cmake_minimum_required(VERSION 3.5...3.11)
project(httpserver)
# Common options
    include_directories(third_party/cpp-httplib
        /usr/include
        /usr/local/include
        /usr/include/pgsql
        /usr/include/postgresql)
    link_directories(/usr/local/lib)
    add_definitions(-pthread -ggdb -O0)
    set(LIBS pthread)
    if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
        set(LIBS ${LIBS} )
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "FreeBSD")
        set(LIBS ${LIBS} )
    else()
        set(LIBS ${LIBS}  ws2_32)
    endif()
    message(NOTICE ${CMAKE_SYSTEM_NAME})
# http server target
    add_executable(httpserver
        src/dbclient.cpp
        src/server.cpp)
    target_link_libraries(httpserver ${LIBS} pq)
# http client target
    add_executable(httpclient
        src/client.cpp)
    target_link_libraries(httpclient ${LIBS})

# test dbclient
    add_executable(testdbclient
        src/testdbclient.cpp
        src/dbclient.cpp)
    target_link_libraries(testdbclient ${LIBS} pq)

