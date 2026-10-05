cmake_minimum_required(VERSION 3.29)
project(piggy C)
set(CMAKE_C_STANDARD 23)

add_library(piggy SHARED piggy.c)
add_executable(dllloader dllloader.c)

if (DEFINED FILE_STEM AND FILE_STEM)
    add_dependencies(dllloader ${FILE_STEM})
endif()
set_target_properties(piggy PROPERTIES OUTPUT_NAME "piggy" PREFIX "")
