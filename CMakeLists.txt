cmake_minimum_required(VERSION 3.16)

project(c_libs)

# Optionally set common flags, include paths, etc.
set(CMAKE_C_STANDARD 11)
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
set(CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}/lib)

file(GLOB lib_dirs lib_srcs/*)
foreach(dir ${lib_dirs})
    if(IS_DIRECTORY "${dir}")
        get_filename_component(lib_name "${dir}" NAME)
        add_subdirectory(${dir} ${CMAKE_BINARY_DIR}/${lib_name})
    endif()
endforeach()
