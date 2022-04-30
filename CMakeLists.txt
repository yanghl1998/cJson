cmake_minimum_required(VERSION 3.16)

project(cjson_test C)

if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall")
endif()

add_library(cjson leptjson.c)
add_executable(cjson_test test.c)
target_link_libraries(cjson_test cjson)