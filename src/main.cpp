#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Render/ShaderProgram.h"
#include "Render/Texture2D.h"
#include "Resources/ResourceManager.h"
#include "Window/Window.h"

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

        auto shader_program = ResourceManager.loadShaderProgram(
            "TriangleShader", "res/Shaders/vertex_shader.txt", "res/Shaders/fragment_shader.txt");

        if (!shader_program) {
            std::cerr << "ERROR WHILE LOADING SHADER PROGRAM" << std::endl;
            return -1;
        }

        auto texture = ResourceManager.loadTexture("DefaultTexture", "res\\Textures\\map_8x8.png"); // map_8x8.png

        // vertex virtual buffer object
        GLuint points_vbo;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);

        // color virtual buffer object
        GLuint color_vbo;
        glGenBuffers(1, &color_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), &colors, GL_STATIC_DRAW);

        // texture virtual buffer object
        GLuint texture_vbo;
        glGenBuffers(1, &texture_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texture_coords), &texture_coords, GL_STATIC_DRAW);

        // vertex array object
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        shader_program->use();
        shader_program->setInt("tex", GL_TEXTURE0);

        glm::mat4 modelMatrix_1(1.f);
        modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(50.f, 50.f, 0.f));

        glm::mat4 modelMatrix_2(1.f);
        modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590.f, 50.f, 0.f));

        glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(Window::Window::m_WindowSize.x), 0.f,
                                                static_cast<float>(Window::Window::m_WindowSize.y), -100.f, 100.f);

        shader_program->setMatrix4("projectionMatrix", projectionMatrix);

        while (!glfwWindowShouldClose(Window.getWindow()))
        {
            glClear(GL_COLOR_BUFFER_BIT);

            shader_program->use();
            glBindVertexArray(vao);
            texture->bind();

            shader_program->setMatrix4("modelMatrix", modelMatrix_1);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            shader_program->setMatrix4("modelMatrix", modelMatrix_2);
            glDrawArrays(GL_TRIANGLES, 0, 3);


            glfwSwapBuffers(Window.getWindow());

            glfwPollEvents();
        }
    }

    glfwTerminate();
    std::cout << "-----------------------" << std::endl << "||||||||||||||||||||||||" << std::endl << "|||Ending GameEngine!|||" << std::endl << "||||||||||||||||||||||||" << std::endl;
    return 0;
}
