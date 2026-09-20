cmake_minimum_required(VERSION 3.10)
project(MyApp)

set(CMAKE_CXX_STANDARD 17)

add_executable(MyApp
    src/main.cpp
    src/shader.hpp
    src/glad.c
    )

target_include_directories(MyApp PRIVATE include
)

find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(MyApp PRIVATE glfw)
