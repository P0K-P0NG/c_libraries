cmake_minimum_required(VERSION 3.16)

project("basic_utils")

if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
    message(STATUS "This project is a top-level one")
endif()

add_library(${PROJECT_NAME})
# Optionally set common flags, include paths, etc.
set(CMAKE_C_STANDARD 11)
# message(STATUS "PATH [${CMAKE_SOURCE_DIR}/lib]")
# set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

file(GLOB srcs ${CMAKE_CURRENT_SOURCE_DIR}/srcs/*.c)
target_sources(${PROJECT_NAME} 
    PRIVATE 
        ${srcs})
target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/includes    
)
# target_link_directories(${PROJECT_NAME} 
#     PRIVATE 
#         ${CMAKE_CURRENT_SOURCE_DIR}/objs)
# set_target_properties(${PROJECT_NAME} PROPERTIES
#     LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
# )