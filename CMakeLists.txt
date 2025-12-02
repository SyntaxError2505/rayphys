cmake_minimum_required(VERSION 3.14)

project(rayphys)

find_package(raylib 3.0 REQUIRED)

add_executable(rayphys src/main.c src/engine.c)
target_include_directories(rayphys PRIVATE include)

target_link_libraries(rayphys raylib)