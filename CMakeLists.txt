cmake_minimum_required(VERSION 3.7)
project(TpConcurrenteAtrevido)

set(CMAKE_CXX_STANDARD 11)
include_directories(.)
file(GLOB SOURCES "./src/*")
set(SOURCE_FILES main.cpp ${SOURCES})
add_executable(TpConcurrenteAtrevido ${SOURCE_FILES})