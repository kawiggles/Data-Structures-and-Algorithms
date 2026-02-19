cmake_minimum_required(VERSION 4.2.3)

project(Data_Structures_and_Algorithms)

add_executable(builddata)

target_sources(builddata
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