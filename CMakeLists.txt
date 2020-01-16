cmake_minimum_required(VERSION 2.8)

project(ParseIPTest)
SET(CMAKE_CXX_STANDARD 17)

set(SOURCES
    main.cpp
    URIHandler.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})
