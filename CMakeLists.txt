cmake_minimum_required(VERSION 3.22)
project(scheduling)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

# https://github.com/jbeder/yaml-cpp
set(YAML_CPP_DIR ~/libs/yaml-cpp)
include_directories(${YAML_CPP_DIR}/include)
link_directories(${YAML_CPP_DIR}/build)

# https://gitlab.com/libeigen/eigen
set(EIGEN_DIR ~/libs/eigen)
include_directories(${EIGEN_DIR})

include_directories(
        code/breakdowns_generators/headers
        code/errors/headers
        code/evaluation/headers
        code/events/headers
        code/genotype/headers
        code/hyperparameter_tuning/headers
        code/job_sequence_generators/headers
        code/jobs/headers
        code/machines/headers
        code/online_scheduling_algorithms/cartesian_genetic_programming/headers
        code/online_scheduling_algorithms/constant_programming/headers
        code/online_scheduling_algorithms/gene_expression_programming/headers
        code/online_scheduling_algorithms/grammatical_evolution/headers
        code/online_scheduling_algorithms/graph_based_genetic_programming/headers
        code/online_scheduling_algorithms/linear_genetic_programming/headers
        code/online_scheduling_algorithms/multi_expression_programming/headers
        code/online_scheduling_algorithms/neural_network/headers
        code/online_scheduling_algorithms/random_programming/headers
        code/online_scheduling_algorithms/structured_grammatical_evolution/headers
        code/online_scheduling_algorithms/stack_based_genetic_programming/headers
        code/online_scheduling_algorithms/tree_based_genetic_programming/headers
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
        code/hyperparameter_tuning/headers/*.h
        code/job_sequence_generators/headers/*.h
        code/jobs/headers/*.h
        code/machines/headers/*.h
        code/online_scheduling_algorithms/cartesian_genetic_programming/headers/*.h
        code/online_scheduling_algorithms/constant_programming/headers/*.h
        code/online_scheduling_algorithms/gene_expression_programming/headers/*.h
        code/online_scheduling_algorithms/grammatical_evolution/headers/*.h
        code/online_scheduling_algorithms/graph_based_genetic_programming/headers/*.h
        code/online_scheduling_algorithms/linear_genetic_programming/headers/*.h
        code/online_scheduling_algorithms/multi_expression_programming/headers/*.h
        code/online_scheduling_algorithms/neural_network/headers/*.h
        code/online_scheduling_algorithms/random_programming/headers/*.h
        code/online_scheduling_algorithms/structured_grammatical_evolution/headers/*.h
        code/online_scheduling_algorithms/stack_based_genetic_programming/headers/*.h
        code/online_scheduling_algorithms/tree_based_genetic_programming/headers/*.h
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
        code/hyperparameter_tuning/sources/*.cpp
        code/job_sequence_generators/sources/*.cpp
        code/jobs/sources/*.cpp
        code/machines/sources/*.cpp
        code/online_scheduling_algorithms/cartesian_genetic_programming/sources/*.cpp
        code/online_scheduling_algorithms/constant_programming/sources/*.cpp
        code/online_scheduling_algorithms/gene_expression_programming/sources/*.cpp
        code/online_scheduling_algorithms/grammatical_evolution/sources/*.cpp
        code/online_scheduling_algorithms/graph_based_genetic_programming/sources/*.cpp
        code/online_scheduling_algorithms/linear_genetic_programming/sources/*.cpp
        code/online_scheduling_algorithms/multi_expression_programming/sources/*.cpp
        code/online_scheduling_algorithms/neural_network/sources/*.cpp
        code/online_scheduling_algorithms/random_programming/sources/*.cpp
        code/online_scheduling_algorithms/structured_grammatical_evolution/sources/*.cpp
        code/online_scheduling_algorithms/stack_based_genetic_programming/sources/*.cpp
        code/online_scheduling_algorithms/tree_based_genetic_programming/sources/*.cpp
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
add_executable(online_scheduling_genotype executables/online_scheduling_genotype.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(topology_enumerator executables/topology_enumerator.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(random_generator executables/random_generator.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(regression_algorithm executables/regression_algorithm.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(simple_experiment executables/simple_experiment.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(experiment_generate_jobs executables/experiments/experiment_generate_jobs.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(experiment_generate_breakdowns executables/experiments/experiment_generate_breakdowns.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(experiment_constant_programming executables/experiments/experiment_constant_programming.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(hyperparameter_tuning_cgp executables/hyperparameter_tuning/hyperparameter_tuning_cgp.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(hyperparameter_tuning_gbgp executables/hyperparameter_tuning/hyperparameter_tuning_gbgp.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(hyperparameter_tuning_ge executables/hyperparameter_tuning/hyperparameter_tuning_ge.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(hyperparameter_tuning_gep executables/hyperparameter_tuning/hyperparameter_tuning_gep.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(hyperparameter_tuning_lgp executables/hyperparameter_tuning/hyperparameter_tuning_lgp.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(hyperparameter_tuning_mep executables/hyperparameter_tuning/hyperparameter_tuning_mep.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(hyperparameter_tuning_nn executables/hyperparameter_tuning/hyperparameter_tuning_nn.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(hyperparameter_tuning_sbgp executables/hyperparameter_tuning/hyperparameter_tuning_sbgp.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(hyperparameter_tuning_sge executables/hyperparameter_tuning/hyperparameter_tuning_sge.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(hyperparameter_tuning_tbgp executables/hyperparameter_tuning/hyperparameter_tuning_tbgp.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(memory_management_experiment executables/memory_management/memory_management_experiment.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(memory_management_genotype executables/memory_management/memory_management_genotype.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(memory_management_algorithm executables/memory_management/memory_management_algorithm.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(run_cgp executables/runs/run_cgp.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(run_gbgp executables/runs/run_gbgp.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(run_tbgp executables/runs/run_tbgp.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(run_ge executables/runs/run_ge.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(run_gep executables/runs/run_gep.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(run_lgp executables/runs/run_lgp.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(run_mep executables/runs/run_mep.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(run_nn executables/runs/run_nn.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(run_rp executables/runs/run_rp.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(run_sbgp executables/runs/run_sbgp.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(run_sge executables/runs/run_sge.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})

target_link_libraries(scheduling yaml-cpp)
target_link_libraries(bit_sum_genotype yaml-cpp)
target_link_libraries(run_examples yaml-cpp)
target_link_libraries(run_example yaml-cpp)
target_link_libraries(run_test yaml-cpp)
target_link_libraries(generate_jobs yaml-cpp)
target_link_libraries(generate_breakdowns yaml-cpp)
target_link_libraries(online_scheduling yaml-cpp)
target_link_libraries(online_scheduling_genotype yaml-cpp)
target_link_libraries(topology_enumerator yaml-cpp)
target_link_libraries(random_generator yaml-cpp)
target_link_libraries(regression_algorithm yaml-cpp)
target_link_libraries(simple_experiment yaml-cpp)
target_link_libraries(experiment_generate_jobs yaml-cpp)
target_link_libraries(experiment_generate_breakdowns yaml-cpp)
target_link_libraries(experiment_constant_programming yaml-cpp)
target_link_libraries(hyperparameter_tuning_cgp yaml-cpp)
target_link_libraries(hyperparameter_tuning_gbgp yaml-cpp)
target_link_libraries(hyperparameter_tuning_ge yaml-cpp)
target_link_libraries(hyperparameter_tuning_gep yaml-cpp)
target_link_libraries(hyperparameter_tuning_lgp yaml-cpp)
target_link_libraries(hyperparameter_tuning_mep yaml-cpp)
target_link_libraries(hyperparameter_tuning_nn yaml-cpp)
target_link_libraries(hyperparameter_tuning_sbgp yaml-cpp)
target_link_libraries(hyperparameter_tuning_sge yaml-cpp)
target_link_libraries(hyperparameter_tuning_tbgp yaml-cpp)
target_link_libraries(memory_management_experiment yaml-cpp)
target_link_libraries(memory_management_genotype yaml-cpp)
target_link_libraries(memory_management_algorithm yaml-cpp)
target_link_libraries(run_cgp yaml-cpp)
target_link_libraries(run_gbgp yaml-cpp)
target_link_libraries(run_tbgp yaml-cpp)
target_link_libraries(run_ge yaml-cpp)
target_link_libraries(run_gep yaml-cpp)
target_link_libraries(run_lgp yaml-cpp)
target_link_libraries(run_mep yaml-cpp)
target_link_libraries(run_nn yaml-cpp)
target_link_libraries(run_rp yaml-cpp)
target_link_libraries(run_sbgp yaml-cpp)
target_link_libraries(run_sge yaml-cpp)

add_custom_target(hyperparameter_tuning
    DEPENDS hyperparameter_tuning_cgp
            hyperparameter_tuning_gbgp
            hyperparameter_tuning_ge
            hyperparameter_tuning_gep
            hyperparameter_tuning_lgp
            hyperparameter_tuning_mep
            hyperparameter_tuning_nn
            hyperparameter_tuning_sbgp
            hyperparameter_tuning_sge
            hyperparameter_tuning_tbgp
)

add_custom_target(runs
    DEPENDS run_cgp
            run_gbgp
            run_tbgp
            run_ge
            run_gep
            run_lgp
            run_mep
            run_nn
            run_rp
            run_sbgp
            run_sge
)