cmake_minimum_required(VERSION 3.24)
project(scheduling)

set(CMAKE_CXX_STANDARD 17)

include_directories(genotype/headers)

file(GLOB PROJECT_HEADERS genotype/headers/*.hpp genotype/headers/*.h)
file(GLOB PROJECT_SOURCES genotype/sources/*.cpp)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})

add_executable(scheduling main.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
