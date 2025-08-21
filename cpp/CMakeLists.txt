cmake_minimum_required(VERSION 3.5...3.11)
project(httpserver)
# Common options
    set(INCLUDE_DIRS third_party/cpp-httplib)
    set(LIB_DIRS /usr/local/lib)
    add_definitions(-pthread -ggdb -O0)
    if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
        set(LIBS pthread)
        # Поиск PostgreSQL через find_package
        find_package(PostgreSQL REQUIRED)
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "FreeBSD")
        set(LIBS pthread)
        # Поиск PostgreSQL через find_package
        find_package(PostgreSQL REQUIRED)
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
        set(LIBS pthread ws2_32)
        find_path(PostgreSQL_INCLUDE_DIRS libpq-fe.h
            PATHS "third_party/postgresql/include/pgsql" # Adjust path to your PostgreSQL installation
            NO_DEFAULT_PATH)

        if(PostgreSQL_INCLUDE_DIRS)
            message(STATUS "Found libpq-fe.h: ${PostgreSQL_INCLUDE_DIRS}")
        endif()

        find_library(PostgreSQL_LIBRARY libpq.lib
             PATHS "third_party/postgresql/lib" # Adjust path
             NO_DEFAULT_PATH)

        if(PostgreSQL_LIBRARY)
            message(STATUS "Found libpq: ${PostgreSQL_LIBRARY}")
        endif()

        if(PostgreSQL_INCLUDE_DIRS AND PostgreSQL_LIBRARY)
            message(STATUS "Found libpq: ${PostgreSQL_LIBRARY}")
            set(PostgreSQL_FOUND true)
        else()
            message(FATAL_ERROR "libpq not found. Please install PostgreSQL or adjust paths.")
        endif()
    endif()

    message(NOTICE ${CMAKE_SYSTEM_NAME})
    
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
    target_link_libraries(httpserver ${LIBS} ${PostgreSQL_LIBRARY})
# http client target
    add_executable(httpclient
        src/client.cpp)
    target_link_libraries(httpclient ${LIBS})

# test dbclient
    add_executable(testdbclient
        src/testdbclient.cpp
        src/dbclient.cpp)
    target_link_libraries(testdbclient ${LIBS} ${PostgreSQL_LIBRARY})

