# Copyright (c) 2019 Clebrain. All rights reserved.

cmake_minimum_required(VERSION 3.13)
project(clebrain)

include_directories(
    Include
    paxbun/Include # Clebrain uses some component of paxbun
)
add_library(clebrain
    Source/bciCompetitionIV/Table.cc
    Source/bciCompetitionIV/TableReader.cc
)

add_executable(clebrain-test Test/Test.cc)
target_link_libraries(clebrain-test clebrain)