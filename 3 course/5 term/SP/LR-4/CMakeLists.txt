cmake_minimum_required(VERSION 3.0.0)
project(LR-4 VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(Threads)

add_executable(LR-4 main.cpp)

target_link_libraries(LR-4 ${CMAKE_THREAD_LIBS_INIT})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)