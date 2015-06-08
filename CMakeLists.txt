cmake_minimum_required(VERSION 2.8.4)
project(HSAT)

SET(CMAKE_C_COMPILER "gcc")
SET(CMAKE_CXX_COMPILER "g++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

set(SOURCE_FILES_MAIN
    cisat.cpp
    include/agents_and_teams/agent.hpp
    include/agents_and_teams/team.hpp
    include/agents_and_teams/multiple_teams.hpp
    include/meta_optimization/search.hpp
    include/meta_optimization/pattern.hpp
    include/meta_optimization/univariate.hpp
    include/utilities/parameters.hpp
    include/utilities/make_random.hpp
    include/utilities/custom_print.hpp
    include/utilities/stats.hpp
    include/problem_statements/ackley.hpp
    src/agents_and_teams/agent.cpp
    src/agents_and_teams/team.cpp
    src/agents_and_teams/multiple_teams.cpp
    src/meta_optimization/search.cpp
    src/meta_optimization/pattern.cpp
    src/meta_optimization/univariate.cpp
    src/utilities/parameters.cpp
    src/utilities/make_random.cpp
    src/utilities/custom_print.cpp
    src/utilities/stats.cpp
    src/problem_statements/ackley.cpp)


add_executable(cisat ${SOURCE_FILES_MAIN})