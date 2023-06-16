cmake_minimum_required(VERSION 3.11)
project(NamedArguments VERSION 0.1.0 LANGUAGES CXX)

add_library(NamedArguments INTERFACE)
target_compile_features(NamedArguments INTERFACE cxx_std_17)
target_include_directories(NamedArguments INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(unit-tests)