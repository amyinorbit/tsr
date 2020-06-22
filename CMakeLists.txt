cmake_minimum_required(VERSION 3.12)
project(tinysr VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(APPLE)
    link_directories(/usr/local/lib)
endif()

include_directories(include)
add_subdirectory(src)