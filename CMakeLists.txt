cmake_minimum_required(VERSION 3.5)
project(gaohuan-c)

add_subdirectory(src)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(SOURCE_FILES main.c)
#add_executable(gaohuan-c ${SOURCE_FILES})