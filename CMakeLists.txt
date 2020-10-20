cmake_minimum_required(VERSION 3.5)

project(helloWorld VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB libSource src/*.h src/*.cc)
add_library(otl STATIC ${libSource})
