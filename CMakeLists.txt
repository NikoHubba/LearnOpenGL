cmake_minimum_required(VERSION 3.10)
project(MyApp)

set(CMAKE_CXX_STANDARD 17)

add_executable(MyApp
    src/main.cpp
    src/shader.hpp
    src/glad.c
    )

# Include directory
target_include_directories(MyApp PRIVATE C:/Users/Nikoh/source/librariesc++/glfw-3.5.1/include)

# Link the library (choose Debug or Release)
target_link_libraries(MyApp PRIVATE
    C:/GLFW_BUILD/src/Debug/glfw3.lib
)
