cmake_minimum_required(VERSION 3.22)

project(basic-opengl VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)

add_subdirectory(glfw)
add_executable(main src/config.h 
                    src/main.cpp 
                    src/glad.c 
                    src/triangle_mesh.h 
                    src/triangle_mesh.cpp)

target_include_directories(main PRIVATE include)
target_link_libraries(main glfw OpenGL::GL)