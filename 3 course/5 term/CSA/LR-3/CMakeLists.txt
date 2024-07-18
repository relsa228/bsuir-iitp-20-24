
cmake_minimum_required(VERSION 3.23)

project(LR_3)

set(CMAKE_CXX_STANDARD 17)

add_executable(LR_3 main.cpp)

SET_TARGET_PROPERTIES(LR_3 PROPERTIES COMPILE_FLAGS "-fopenmp"
        LINK_FLAGS "-fopenmp")