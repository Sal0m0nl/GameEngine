#include <iostream>
#include <chrono>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Render/ShaderProgram.h"
#include "Render/Texture2D.h"
#include "Resources/ResourceManager.h"
#include "Window/Window.h"

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Render/AnimatedSprite.h"
#include "Render/Sprite.h"

GLfloat points[] = {
    0.0f, 50.f, 0.0f,
    50.0f, -50.0f, 0.0f,
   -50.0f, -50.0f, 0.0f,
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
};

GLfloat texture_coords[] = {
    0.5f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
};

int main(int argc, char** argv)
{
    std::cout << "||||||||||||||||||||||||" << std::endl << "||Starting GameEngine!||" << std::endl << "||||||||||||||||||||||||" << std::endl;
    Window::Window Window(glm::ivec2(640, 480), "Game Engine");

    {
        ResourceManager::ResourceManager ResourceManager(argv[0]);

        std::shared_ptr<Render::ShaderProgram> p_ShaderProgram = ResourceManager.loadShaderProgram(
            "TriangleShader", "res/Shaders/vertex_shader.txt", "res/Shaders/fragment_shader.txt");

        if (!p_ShaderProgram) {
            std::cerr << "ERROR WHILE LOADING SHADER PROGRAM" << std::endl;
            return -1;
        }

        std::shared_ptr<Render::ShaderProgram> p_SpriteShaderProgram = ResourceManager.loadShaderProgram(
    "SpritesShader", "res/Shaders/vSprite.txt", "res/Shaders/fSprite.txt");

        if (!p_SpriteShaderProgram) {
            std::cerr << "ERROR WHILE LOADING SHADER PROGRAM" << std::endl;
            return -1;
        }

        std::shared_ptr<Render::Texture2D> texture = ResourceManager.loadTexture("DefaultTexture", "res\\Textures\\map_8x8.png");

        std::vector<std::string> subTexturesNames = {
            "Bird",
            "Flag",
            "Star_1",
            "Star_2",
            "Star_3",
            "Star_4",
            "Cross_1",
            "Cross_2",
            "BigBoom_1_1",
            "BigBoom_1_2",
            "BigBoom_2_1",
            "BigBoom_2_2",
            "Boom_1",
            "Boom_2",
            "Boom_3",
        };
        std::shared_ptr<Render::Texture2D> pTextureAtlas = ResourceManager.loadTextuteAtlas("DefaultTextureAtlas", "res\\Textures\\map_16x16.png", std::move(subTexturesNames), 16, 16);

        std::shared_ptr<Render::Sprite> p_Sprite = ResourceManager.loadSprite("DefaultSprite", "DefaultTextureAtlas", "SpritesShader", "Star_1", 200, 100);
        p_Sprite->setPosition(glm::vec2(0.0f, 0.0f));

        std::shared_ptr<Render::AnimatedSprite> p_animatedSprite = ResourceManager.loadAnimatedSprite("DefaultAnimatedSprite", "DefaultTextureAtlas", "SpritesShader", "Flag", 400, 400);

        std::vector<std::pair<std::string, uint64_t>> birdStates;
        birdStates.emplace_back(std::make_pair(std::string("Bird"), 1000000000));
        birdStates.emplace_back(std::make_pair(std::string("Flag"), 1000000000));

        std::vector<std::pair<std::string, uint64_t>> boomStates;
        boomStates.emplace_back(std::make_pair(std::string("Boom_1"), 1000000000));
        boomStates.emplace_back(std::make_pair(std::string("Boom_2"), 1000000000));
        boomStates.emplace_back(std::make_pair(std::string("Boom_3"), 1000000000));

        p_animatedSprite->insertState(std::string("Bird"), std::move(birdStates));
        p_animatedSprite->insertState(std::string("Boom"), std::move(boomStates));

        p_animatedSprite->setState("Boom");

        p_animatedSprite->setPosition(glm::vec2(300.0f, 0.0f));


        // // vertex virtual buffer object
        // GLuint points_vbo;
        // glGenBuffers(1, &points_vbo);
        // glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
        //
        // // color virtual buffer object
        // GLuint color_vbo;
        // glGenBuffers(1, &color_vbo);
        // glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(colors), &colors, GL_STATIC_DRAW);
        //
        // // texture virtual buffer object
        // GLuint texture_vbo;
        // glGenBuffers(1, &texture_vbo);
        // glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(texture_coords), &texture_coords, GL_STATIC_DRAW);
        //
        // // vertex array object
        // GLuint vao;
        // glGenVertexArrays(1, &vao);
        // glBindVertexArray(vao);
        //
        // glEnableVertexAttribArray(0);
        // glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        //
        // glEnableVertexAttribArray(1);
        // glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
        // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        //
        // glEnableVertexAttribArray(2);
        // glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
        // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        //
        // p_ShaderProgram->use();
        // p_ShaderProgram->setInt("tex", GL_TEXTURE0);
        //
        // glm::mat4 modelMatrix_1(1.f);
        // modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(50.f, 50.f, 0.f));
        //
        // glm::mat4 modelMatrix_2(1.f);
        // modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590.f, 50.f, 0.f));
        //
        glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(Window::Window::m_WindowSize.x), 0.f,
                                                 static_cast<float>(Window::Window::m_WindowSize.y), -100.f, 100.f);
        //
        // p_ShaderProgram->setMatrix4("projectionMatrix", projectionMatrix);

        p_SpriteShaderProgram->use();
        p_SpriteShaderProgram->setMatrix4("projectionMatrix", projectionMatrix);
        p_SpriteShaderProgram->setInt("tex", GL_TEXTURE0);

        auto lastTime = std::chrono::high_resolution_clock::now();

        while (!glfwWindowShouldClose(Window.getWindow()))
        {
            auto currentTime = std::chrono::high_resolution_clock::now();
            uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
            lastTime = currentTime;
            p_animatedSprite->update(duration);

            glClear(GL_COLOR_BUFFER_BIT);

            // p_ShaderProgram->use();
            // glBindVertexArray(vao);
            // texture->bind();
            //
            // p_ShaderProgram->setMatrix4("modelMatrix", modelMatrix_1);
            // glDrawArrays(GL_TRIANGLES, 0, 3);
            //
            // p_ShaderProgram->setMatrix4("modelMatrix", modelMatrix_2);
            // glDrawArrays(GL_TRIANGLES, 0, 3);

            p_Sprite->render();

            p_animatedSprite->render();

            glfwSwapBuffers(Window.getWindow());

            glfwPollEvents();
        }
    }

    glfwTerminate();
    std::cout << "-----------------------" << std::endl << "||||||||||||||||||||||||" << std::endl << "|||Ending GameEngine!|||" << std::endl << "||||||||||||||||||||||||" << std::endl;
    return 0;
}
