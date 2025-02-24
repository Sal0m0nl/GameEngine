cmake_minimum_required(VERSION 3.30 FATAL_ERROR)
project(GameEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(GameEngine src/main.cpp
        src/Render/ShaderProgram.cpp
        src/Render/ShaderProgram.h
        src/Resources/ResourceManager.cpp
        src/Resources/ResourceManager.h
        res/Textures/stb_image.h
        src/Render/Texture2D.cpp
        src/Render/Texture2D.h
        src/Window/Window.cpp
        src/Window/Window.h
)

#  Linking GLFW
add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# Linking GLAD
add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)