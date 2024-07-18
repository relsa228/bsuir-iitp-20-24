cmake_minimum_required(VERSION 3.9)
project(LR_1)
enable_language(ASM_NASM)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> \
    <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

set_source_files_properties(src/strlen.asm PROPERTIES COMPILE_FLAGS "-g -Fdwarf")

set(CMAKE_C_STANDARD 11)

add_executable(LR_1
        asmHelper.asm
        main.c)
