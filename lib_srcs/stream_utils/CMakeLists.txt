cmake_minimum_required(VERSION 3.16)

project("stream_utils")

if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
    message(STATUS "This project is a top-level one")
endif()

add_library(${PROJECT_NAME})

# Optionally set common flags, include paths, etc.
set(CMAKE_C_STANDARD 11)
set(dependencies basic_utils string_utils generics)
set(dependency_includes)
foreach(dep IN LISTS dependencies)
    list(APPEND dependency_includes "${CMAKE_SOURCE_DIR}/lib_srcs/${dep}/includes")
endforeach()

file(GLOB srcs ${CMAKE_CURRENT_SOURCE_DIR}/srcs/*.c)
target_sources(${PROJECT_NAME} 
    PRIVATE 
        ${srcs})
target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/includes    
        ${dependency_includes}
)
target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        ${dependencies})