cmake_minimum_required(VERSION 3.14)
project(Euler_Method)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        scale.h
        euler_method.h
        one_variable_function.h
        parameter_function.h
)
add_executable(Picard_iteration ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Picard_iteration sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
