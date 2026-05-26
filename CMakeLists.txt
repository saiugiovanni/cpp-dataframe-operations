cmake_minimum_required(VERSION 3.23)
project(DataFrameChallenge2_BASE)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DataFrameChallenge2_BASE
        checkChallenge.cpp
        checkChallenge.h
        Column.cpp
        Column.h
        DataFrame.cpp
        DataFrame.h
        main.cpp
        TestValues1.h
        TestValues2.h
        TestValues3.h
        TestValues4.h)
