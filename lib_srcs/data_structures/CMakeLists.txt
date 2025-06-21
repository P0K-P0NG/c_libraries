cmake_minimum_required(VERSION 3.16)

project("data_structures")

if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
    message(STATUS "This project is a top-level one")
endif()

# Optionally set common flags, include paths, etc.
set(CMAKE_C_STANDARD 11)

file(GLOB lib_dirs */)
foreach(dir ${lib_dirs})
    if(IS_DIRECTORY "${dir}")
        get_filename_component(lib_name "${dir}" NAME)
        add_subdirectory(${dir} ${CMAKE_BINARY_DIR}/${lib_name})
    endif()
endforeach()