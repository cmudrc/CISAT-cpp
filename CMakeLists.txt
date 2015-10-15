cmake_minimum_required(VERSION 2.8.4)
project(CISAT)

#Throws error when uncommented:
#error: ambiguous instructions require an explicit suffix (could be 'filds', or 'fildl')
#set(CMAKE_C_COMPILER "gcc")
#set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

set(SOURCE_FILES_FLUID_NETWORK
    cisat.cpp

    include/problem_statements/fluid_network.hpp
    src/problem_statements/fluid_network.cpp

    include/problem_statements/graph.hpp
    src/problem_statements/graph.cpp

    include/agents_and_teams/agent.hpp
    include/agents_and_teams/team.hpp
    include/agents_and_teams/multiple_teams.hpp
    include/meta_optimization/search.hpp
    include/meta_optimization/pattern.hpp
    include/meta_optimization/univariate.hpp
    include/utilities/parameterset.hpp
    include/utilities/make_random.hpp
    include/utilities/custom_print.hpp
    include/utilities/stats.hpp
    include/utilities/optimization.hpp
    include/utilities/matrix_operations.hpp
    include/utilities/write_x3d.hpp
    src/agents_and_teams/agent.cpp
    src/agents_and_teams/team.cpp
    src/agents_and_teams/multiple_teams.cpp
    src/meta_optimization/search.cpp
    src/meta_optimization/pattern.cpp
    src/meta_optimization/univariate.cpp
    src/utilities/parameterset.cpp
    src/utilities/make_random.cpp
    src/utilities/custom_print.cpp
    src/utilities/stats.cpp
    src/utilities/optimization.cpp
    src/utilities/matrix_operations.cpp
    src/utilities/write_x3d.cpp)


set(SOURCE_FILES_STRUCTURE
    cisat.cpp

    include/problem_statements/structure.hpp
    src/problem_statements/structure.cpp

    include/problem_statements/graph.hpp
    src/problem_statements/graph.cpp

    include/agents_and_teams/agent.hpp
    include/agents_and_teams/team.hpp
    include/agents_and_teams/multiple_teams.hpp
    include/meta_optimization/search.hpp
    include/meta_optimization/pattern.hpp
    include/meta_optimization/univariate.hpp
    include/utilities/parameterset.hpp
    include/utilities/make_random.hpp
    include/utilities/custom_print.hpp
    include/utilities/stats.hpp
    include/utilities/optimization.hpp
    include/utilities/matrix_operations.hpp
    include/utilities/write_x3d.hpp
    src/agents_and_teams/agent.cpp
    src/agents_and_teams/team.cpp
    src/agents_and_teams/multiple_teams.cpp
    src/meta_optimization/search.cpp
    src/meta_optimization/pattern.cpp
    src/meta_optimization/univariate.cpp
    src/utilities/parameterset.cpp
    src/utilities/make_random.cpp
    src/utilities/custom_print.cpp
    src/utilities/stats.cpp
    src/utilities/optimization.cpp
    src/utilities/matrix_operations.cpp
    src/utilities/write_x3d.cpp)

add_executable(cisat_fluid_network ${SOURCE_FILES_FLUID_NETWORK})
add_executable(cisat_structure ${SOURCE_FILES_STRUCTURE})