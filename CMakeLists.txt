cmake_minimum_required(VERSION 2.8.4)
project(HSAT)

# Code compiles slightly faster with
#set(CMAKE_C_COMPILER "gcc")
#set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

set(SOURCE_FILES_MAIN
    cisat.cpp

    include/problem_statements/fluid_channels.hpp
    src/problem_statements/fluid_channels.cpp

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
    src/utilities/optimization.cpp)


add_executable(cisat ${SOURCE_FILES_MAIN})