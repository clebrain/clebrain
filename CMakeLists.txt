# Copyright (c) 2019 Clebrain. All rights reserved.

cmake_minimum_required(VERSION 3.13)
project(clebrain)
enable_testing()

file(
    READ
    Config/bciCompetitionIV/DataList.txt
    CLEBRAIN_BCICOMPETITIONIV_DATA_LIST_TXT
)
string(
    REGEX
    MATCHALL
    "[^\n]+"
    CLEBRAIN_BCICOMPETITIONIV_DATA_LIST
    "${CLEBRAIN_BCICOMPETITIONIV_DATA_LIST_TXT}")

set(
    CLEBRAIN_BCICOMPETITIONIV_DATA_DIR
    "${PROJECT_SOURCE_DIR}/../clebrain-data/"
)

foreach(FILENAME ${CLEBRAIN_BCICOMPETITIONIV_DATA_LIST})
    if (NOT EXISTS "${CLEBRAIN_BCICOMPETITIONIV_DATA_DIR}${FILENAME}")
        message(
            FATAL_ERROR
            "BCICompetitionIV Data file ${FILENAME} is not found."
        )
    endif()
endforeach()

include_directories(
    Include
    paxbun/Include # Clebrain uses some component of paxbun
)
add_library(
    clebrain-bcicompetitioniv
    Source/bciCompetitionIV/Table.cc
)

add_executable(
    clebrain-bcicompetitioniv-test-table
    Test/bciCompetitionIV/Table.cc
)
target_link_libraries(
    clebrain-bcicompetitioniv-test-table
    clebrain-bcicompetitioniv
)
target_compile_definitions(
    clebrain-bcicompetitioniv-test-table
    PUBLIC
    "-DCLEBRAIN_BCICOMPETITIONIV_DATA_DIR=\"${CLEBRAIN_BCICOMPETITIONIV_DATA_DIR}\""
)
add_test(
    bcicompetitioniv-table
    clebrain-bcicompetitioniv-test-table
)