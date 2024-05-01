cmake_minimum_required(VERSION 3.24)
project(scheduling)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

# https://github.com/jbeder/yaml-cpp
set(YAML_CPP_DIR ~/libs/yaml-cpp)
include_directories(${YAML_CPP_DIR}/include)
link_directories(${YAML_CPP_DIR}/build)

include_directories(
        code/errors/headers
        code/evaluation/headers
        code/events/headers
        code/genotype/headers
        code/job_sequence_generators/headers
        code/jobs/headers
        code/machines/headers
        code/online_scheduling/headers
        code/optimization/headers
        code/optimization_algorithms/headers
        code/parsers/headers
        code/paths/headers
        code/problems/headers
        code/random/headers
        code/schedulers/headers
        code/serializers/headers
        code/simulator/headers
        code/topology/headers
        code/utils/headers
)

file(GLOB PROJECT_HEADERS
        code/errors/headers/*.h
        code/evaluation/headers/*.h
        code/events/headers/*.h
        code/genotype/headers/*.h
        code/job_sequence_generators/headers/*.h
        code/jobs/headers/*.h
        code/machines/headers/*.h
        code/online_scheduling/headers/*.h
        code/optimization/headers/*.h
        code/optimization_algorithms/headers/*.h
        code/parsers/headers/*.h
        code/paths/headers/*.h
        code/problems/headers/*.h
        code/random/headers/*.h
        code/schedulers/headers/*.h
        code/serializers/headers/*.h
        code/simulator/headers/*.h
        code/topology/headers/*.h
        code/utils/headers/*.h
)

file(GLOB PROJECT_SOURCES
        code/errors/sources/*.cpp
        code/evaluation/sources/*.cpp
        code/events/sources/*.cpp
        code/genotype/sources/*.cpp
        code/job_sequence_generators/sources/*.cpp
        code/jobs/sources/*.cpp
        code/machines/sources/*.cpp
        code/online_scheduling/sources/*.cpp
        code/optimization/sources/*.cpp
        code/optimization_algorithms/sources/*.cpp
        code/parsers/sources/*.cpp
        code/paths/sources/*.cpp
        code/problems/sources/*.cpp
        code/random/sources/*.cpp
        code/schedulers/sources/*.cpp
        code/serializers/sources/*.cpp
        code/simulator/sources/*.cpp
        code/topology/sources/*.cpp
        code/utils/sources/*.cpp
)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})

add_executable(scheduling main.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})

target_link_libraries(scheduling yaml-cpp)
