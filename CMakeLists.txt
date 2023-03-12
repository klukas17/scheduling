cmake_minimum_required(VERSION 3.24)
project(scheduling)

set(CMAKE_CXX_STANDARD 17)

# https://github.com/jbeder/yaml-cpp
set(YAML_CPP_DIR ~/libs/yaml-cpp)
include_directories(${YAML_CPP_DIR}/include)
link_directories(${YAML_CPP_DIR}/build)

include_directories(genotype/headers parsers/headers)

file(GLOB PROJECT_HEADERS genotype/headers/*.hpp genotype/headers/*.h parsers/headers/*.hpp parsers/headers/*.h)
file(GLOB PROJECT_SOURCES genotype/sources/*.cpp parsers/sources/*.cpp)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})

add_executable(scheduling main.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})

target_link_libraries(scheduling yaml-cpp)