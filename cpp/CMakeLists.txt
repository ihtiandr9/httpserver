cmake_minimum_required(VERSION 3.5...3.11)
project(httpserver)
# Common options
    set(INCLUDE_DIRS third_party/cpp-httplib)
    set(LIB_DIRS /usr/local/lib)
    add_definitions(-pthread -ggdb -O0)
    if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
        set(LIBS pthread)
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "FreeBSD")
        set(LIBS pthread)
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
        set(LIBS pthread ws2_32)
    endif()
    message(NOTICE ${CMAKE_SYSTEM_NAME})
# Поиск PostgreSQL через find_package
    find_package(PostgreSQL REQUIRED)
    include_directories(${INCLUDE_DIRS}
        ${PostgreSQL_INCLUDE_DIRS})
    link_directories(${LIB_DIRS})
    
    # Проверка результата поиска
    if(NOT PostgreSQL_FOUND)
        message(FATAL_ERROR "PostgreSQL не найден! Установите libpq-dev или аналог.")
    endif()
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

