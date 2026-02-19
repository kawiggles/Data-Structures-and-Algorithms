cmake_minimum_required(VERSION 4.2.3)

project(Data_Structures_and_Algorithms)

add_executable(build)

target_sources(build
    PRIVATE
        src/main.c
        src/linkedlist.c
        
    
    PUBLIC
        FILE_SET headers
        TYPE HEADERS
        BASE_DIRS
            include
        FILES
            include/linkedlist.h
)