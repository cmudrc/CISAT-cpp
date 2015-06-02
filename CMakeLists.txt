cmake_minimum_required(VERSION 2.8.4)
project(HSAT)

SET(CMAKE_C_COMPILER "gcc")
SET(CMAKE_CXX_COMPILER "g++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

set(SOURCE_FILES_MAIN
    src/cisat.cpp
    include/agent_team/agent.hpp
    include/agent_team/team.hpp
    include/agent_team/multipleteams.hpp
    include/meta_optim/search.hpp
    include/meta_optim/pattern.hpp
    include/meta_optim/univariate.hpp
    include/utils/objective.hpp
    include/utils/parameters.hpp
    include/utils/makerandom.hpp
    include/utils/customprint.hpp
    include/utils/stats.hpp
    src/agent_team/agent.cpp
    src/agent_team/team.cpp
    src/agent_team/multipleteams.cpp
    src/meta_optim/search.cpp
    src/meta_optim/pattern.cpp
    src/meta_optim/univariate.cpp
    src/utils/parameters.cpp
    src/utils/objective.cpp
    src/utils/makerandom.cpp
    src/utils/customprint.cpp
    src/utils/stats.cpp)

add_executable(cisat ${SOURCE_FILES_MAIN})