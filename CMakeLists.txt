# Copyright (c) 2019 Clebrain. All rights reserved.

cmake_minimum_required(VERSION 3.13)
project(clebrain)

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

foreach(FILENAME ${CLEBRAIN_BCICOMPETITIONIV_DATA_LIST})
    if (NOT EXISTS "${PROJECT_SOURCE_DIR}/../clebrain-data/${FILENAME}")
        message(
            FATAL_ERROR
            "Data file ${FILENAME} is not found.\n${PROJECT_SOURCE_DIR}/../clebrain-data/${FILENAME}"
        )
    endif()
endforeach()

include_directories(
    Include
    paxbun/Include # Clebrain uses some component of paxbun
)
add_library(clebrain-bcicompetitioniv
    Source/bciCompetitionIV/Table.cc
    Source/bciCompetitionIV/TableReader.cc
)

add_executable(clebrain-bcicompetitioniv-test-table Test/Test.cc)
target_link_libraries(clebrain-bcicompetitioniv-test-table clebrain-bcicompetitioniv)