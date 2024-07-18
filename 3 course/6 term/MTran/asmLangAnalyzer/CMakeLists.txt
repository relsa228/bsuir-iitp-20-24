cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_COMPILER "clang")

project(asmlanganalyzer CXX)

add_executable(asmlanganalyzer 
    src/services/lexAnalizeService.cpp 
    src/services/tableCreateService.cpp 
    src/services/syntaxTreeService.cpp
    src/services/semanticAnalizeService.cpp
    
    src/models/token.cpp
    src/models/syntaxTreeNode.cpp

    src/supportingFiles/lexicalBase.cpp 
    src/supportingFiles/syntaxBase.cpp
    src/supportingFiles/semanticBase.cpp

    src/main.cpp)