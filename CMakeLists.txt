cmake_minimum_required(VERSION 3.24)
project(scheduling)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

# https://github.com/jbeder/yaml-cpp
set(YAML_CPP_DIR ~/libs/yaml-cpp)
include_directories(${YAML_CPP_DIR}/include)
link_directories(${YAML_CPP_DIR}/build)

include_directories(
        code/breakdowns_generators/headers
        code/errors/headers
        code/evaluation/headers
        code/events/headers
        code/genotype/headers
        code/job_sequence_generators/headers
        code/jobs/headers
        code/machines/headers
        code/online_scheduling_algorithms/random_programming/headers
        code/online_scheduling_algorithms/constant_programming/headers
        code/optimization/headers
        code/optimization_algorithms/headers
        code/optimization_scheduling/headers
        code/parsers/headers
        code/paths/headers
        code/problems/headers
        code/random/headers
        code/schedulers/headers
        code/serializers/headers
        code/simulator/headers
        code/topology/headers
        code/topology_enumerators/headers
        code/utils/headers
)

file(GLOB PROJECT_HEADERS
        code/breakdowns_generators/headers/*.h
        code/errors/headers/*.h
        code/evaluation/headers/*.h
        code/events/headers/*.h
        code/genotype/headers/*.h
        code/job_sequence_generators/headers/*.h
        code/jobs/headers/*.h
        code/machines/headers/*.h
        code/online_scheduling_algorithms/random_programming/headers/*.h
        code/online_scheduling_algorithms/constant_programming/headers/*.h
        code/optimization/headers/*.h
        code/optimization_algorithms/headers/*.h
        code/optimization_scheduling/headers/*.h
        code/parsers/headers/*.h
        code/paths/headers/*.h
        code/problems/headers/*.h
        code/random/headers/*.h
        code/schedulers/headers/*.h
        code/serializers/headers/*.h
        code/simulator/headers/*.h
        code/topology/headers/*.h
        code/topology_enumerators/headers/*.h
        code/utils/headers/*.h
)

file(GLOB PROJECT_SOURCES
        code/breakdowns_generators/sources/*.cpp
        code/errors/sources/*.cpp
        code/evaluation/sources/*.cpp
        code/events/sources/*.cpp
        code/genotype/sources/*.cpp
        code/job_sequence_generators/sources/*.cpp
        code/jobs/sources/*.cpp
        code/machines/sources/*.cpp
        code/online_scheduling_algorithms/random_programming/sources/*.cpp
        code/online_scheduling_algorithms/constant_programming/sources/*.cpp
        code/optimization/sources/*.cpp
        code/optimization_algorithms/sources/*.cpp
        code/optimization_scheduling/sources/*.cpp
        code/parsers/sources/*.cpp
        code/paths/sources/*.cpp
        code/problems/sources/*.cpp
        code/random/sources/*.cpp
        code/schedulers/sources/*.cpp
        code/serializers/sources/*.cpp
        code/simulator/sources/*.cpp
        code/topology/sources/*.cpp
        code/topology_enumerators/sources/*.cpp
        code/utils/sources/*.cpp
)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})

add_executable(scheduling main.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(bit_sum_genotype executables/bit_sum_genotype.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(run_examples executables/run_examples.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(run_example executables/run_example.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(run_test executables/run_test.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(generate_jobs executables/generate_jobs.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(generate_breakdowns executables/generate_breakdowns.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(online_scheduling executables/online_scheduling.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(topology_enumerator executables/topology_enumerator.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})

target_link_libraries(scheduling yaml-cpp)
target_link_libraries(bit_sum_genotype yaml-cpp)
target_link_libraries(run_examples yaml-cpp)
target_link_libraries(run_example yaml-cpp)
target_link_libraries(run_test yaml-cpp)
target_link_libraries(generate_jobs yaml-cpp)
target_link_libraries(generate_breakdowns yaml-cpp)
target_link_libraries(online_scheduling yaml-cpp)
target_link_libraries(topology_enumerator yaml-cpp)
