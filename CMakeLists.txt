cmake_minimum_required(VERSION 3.30 FATAL_ERROR)
project(GameEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(GameEngine main.cpp)

#  Linking GLFW
add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# Linking GLAD
add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)