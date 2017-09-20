cmake_minimum_required(VERSION 3.8)
project(BPTree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Node.cpp Node.h wrap.cpp wrap.h)
add_executable(BPTree ${SOURCE_FILES})