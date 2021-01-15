cmake_minimum_required(VERSION 3.5)

project(libcsv VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_VERBOSE_MAKEFILE ON)

file(GLOB libSource src/*.h src/*.cc)
add_library(csv STATIC ${libSource})
