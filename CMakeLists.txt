cmake_minimum_required(VERSION 4.2.3)

project(Data_Structures_and_Algorithms)

add_executable(buildstruct)

target_sources(buildstruct
    PRIVATE
        src/main.c
        src/data.c
        src/linkedlist.c
        src/manage.c
        src/algo.c
    
    PUBLIC
        FILE_SET headers
        TYPE HEADERS
        BASE_DIRS
            include
        FILES
            include/data.h
            include/linkedlist.h
            include/manage.h
            include/algo.h
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
