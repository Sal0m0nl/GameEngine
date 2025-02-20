#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Render/ShaderProgram.h"
#include "Resources/ResourceManager.h"

int g_windowSizeX = 640;
int g_windowSizeY = 480;

GLfloat points[] = {
    0.0f, 0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
  -0.5f, -0.5f, 0.0f,
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
};

void glfwWindowResizedCallback(GLFWwindow* p_Window, int width, int height)
{
    g_windowSizeX = width;
    g_windowSizeY = height;

    glViewport(0, 0, width, height);
}

void glfwPressedEscapeCallback(GLFWwindow* p_Window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(p_Window, true);
    }
}

int main(int argc, char** argv)
{
    std::cout << "||||||||||||||||||||||||" << std::endl << "||Starting GameEngine!||" << std::endl << "||||||||||||||||||||||||" << std::endl;

    if (!glfwInit())
    {
        std::cout << "Error while loading GLFW..." << std::endl;
        return -1;
    }

    GLFWwindow* p_Window = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "Game Engine", nullptr, nullptr);
    if (!p_Window)
    {
        glfwTerminate();
        std::cout << "Failed to create window..." << std::endl;
        return -1;
    }

    glfwSetWindowSizeCallback(p_Window, glfwWindowResizedCallback);
    glfwSetKeyCallback(p_Window, glfwPressedEscapeCallback);

    glfwMakeContextCurrent(p_Window);

    if (!gladLoadGL())
    {
        std::cout << "Error while loading GLAD..." << std::endl;
        return -1;
    }

    glClearColor(1, 0, 1, 1);

    {
        ResourceManager::ResourceManager ResourceManager(argv[0]);

        auto shader_program = ResourceManager.loadShaderProgram(
            "TriangleShader", "res/Shaders/vertex_shader.txt", "res/Shaders/fragment_shader.txt");

        if (!shader_program) {
            std::cerr << "ERROR WHILE LOADING SHADER PROGRAM" << std::endl;
            return -1;
        }

        ResourceManager.loadTexture("DefaultTexture", "res\\Textures\\map_16x16.png");



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

        while (!glfwWindowShouldClose(p_Window))
        {
            glClear(GL_COLOR_BUFFER_BIT);

            shader_program->use();
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(p_Window);

            glfwPollEvents();
        }
    }

    glfwTerminate();
    std::cout << "||||||||||||||||||||||||" << std::endl << "|||Ending GameEngine!|||" << std::endl << "||||||||||||||||||||||||" << std::endl;
    return 0;
}
