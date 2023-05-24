cmake_minimum_required(VERSION 3.1...3.22)

project(zutil
    LANGUAGES CXX)

find_package(Catch2 REQUIRED)

add_subdirectory(test)
