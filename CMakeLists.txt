cmake_minimum_required(VERSION 3.12)

project(
    link-keeper 
    VERSION 1.0 
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
