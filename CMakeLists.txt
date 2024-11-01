cmake_minimum_required(VERSION 3.27)

project(calculator)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE INTERFACES "interface/*.cpp")

file(GLOB SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "lib/*/")

set(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/operators")
file(MAKE_DIRECTORY ${OUTPUT_DIRECTORY})
set(LIBRARY_OUTPUT_PATH ${OUTPUT_DIRECTORY})

foreach(SUBDIR ${SUBDIRS})
    if(IS_DIRECTORY ${SUBDIR})
        get_filename_component(LIB_NAME ${SUBDIR} NAME)

        file(GLOB ADDITION_SOURCES "${SUBDIR}/*.cpp")

        if(NOT ADDITION_SOURCES)
            message(FATAL_ERROR "No source files found in ${SUBDIR}")
        endif()

        add_library(${LIB_NAME} SHARED ${ADDITION_SOURCES})

        set_target_properties(${LIB_NAME} PROPERTIES OUTPUT_NAME ${LIB_NAME} PREFIX "")
    endif()
endforeach()

file(GLOB_RECURSE SOURCES "source/*.cpp")

add_executable(${PROJECT_NAME} ${INTERFACES} ${SOURCES})
