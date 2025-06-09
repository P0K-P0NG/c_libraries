cmake_minimum_required(VERSION 3.16)

project("string_utils")

if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
    message(STATUS "This project is a top-level one")
endif()

add_library(${PROJECT_NAME})

# Optionally set common flags, include paths, etc.
set(CMAKE_C_STANDARD 11)

file(GLOB srcs ${CMAKE_CURRENT_SOURCE_DIR}/srcs/*.c)
target_sources(${PROJECT_NAME} 
    PRIVATE 
        ${srcs})
target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/includes    
)

file(GLOB test_srcs ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.c)
foreach(test_src IN LISTS test_srcs)
    get_filename_component(test ${test_src} NAME_WE)
    add_executable(${test} ${test_src})
    target_include_directories(${test}
        PRIVATE 
            ${CMAKE_CURRENT_SOURCE_DIR}/includes
    )
    target_link_libraries(${test}
        PRIVATE
            ${PROJECT_NAME})
    add_test(${test} ${test})
endforeach()