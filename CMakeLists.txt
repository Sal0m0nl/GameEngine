cmake_minimum_required(VERSION 3.30 FATAL_ERROR)
project(GameEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(GameEngine
        src/main.cpp
        src/Resources/ResourceManager.cpp
        src/Resources/ResourceManager.h

        res/Textures/stb_image.h

        src/Render/Texture2D.cpp
        src/Render/Texture2D.h
        src/Render/Sprite.cpp
        src/Render/Sprite.h
        src/Render/VertexBuffer.cpp
        src/Render/VertexBuffer.h
        src/Render/IndexBuffer.cpp
        src/Render/IndexBuffer.h
        src/Render/VertexArray.cpp
        src/Render/VertexArray.h
        src/Render/AnimatedSprite.cpp
        src/Render/AnimatedSprite.h
        src/Render/VertexBufferLayout.cpp
        src/Render/VertexBufferLayout.h
        src/Render/Renderer.cpp
        src/Render/Renderer.h
        src/Render/ShaderProgram.cpp
        src/Render/ShaderProgram.h

        src/Game/Game.cpp
        src/Game/Game.h
        src/Game/Tank.cpp
        src/Game/Tank.h

)

#  Linking GLFW
add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# Linking GLAD
add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

# Linking glm
# include_directories(external/glm)
add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME} glm)


set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)