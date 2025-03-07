#include <iostream>
#include <chrono>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Resources/ResourceManager.h"
#include "Game/Game.h"
#include "Render/Sprite.h"

#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>


glm::ivec2 g_WindowSize(640, 480);

GameEngine::Game g_game(g_WindowSize);

void glfwWindowResizedCallback(GLFWwindow* p_Window, int width, int height)
{
    g_WindowSize.x = width;
    g_WindowSize.y = height;

    glViewport(0, 0, width, height);
}

void glfwPressedEscapeCallback(GLFWwindow* p_Window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(p_Window, true);
    }
    g_game.setKey(key, action);
}

int main(int argc, char** argv)
{
    std::cout << "||||||||||||||||||||||||" << std::endl << "||Starting GameEngine!||" << std::endl << "||||||||||||||||||||||||" << std::endl;

    if (!glfwInit())
    {
        std::cout << "Error while loading GLFW..." << std::endl;
        return -1;
    }

    GLFWwindow *p_Window = glfwCreateWindow(g_WindowSize.x, g_WindowSize.y, "Game Engine", nullptr, nullptr);
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

    glClearColor(0, 0, 0, 1);

    {
        ResourceManager::setExecutablePath(argv[0]);

        g_game.init();

        auto lastTime = std::chrono::high_resolution_clock::now();

        while (!glfwWindowShouldClose(p_Window))
        {
            auto currentTime = std::chrono::high_resolution_clock::now();
            uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
            lastTime = currentTime;

            g_game.update(duration);

            glClear(GL_COLOR_BUFFER_BIT);

            g_game.render();

            glfwSwapBuffers(p_Window);

            glfwPollEvents();
        }
    }

    glfwTerminate();

    ResourceManager::unloadAllResources();

    std::cout << "-----------------------" << std::endl << "||||||||||||||||||||||||" << std::endl << "|||Ending GameEngine!|||" << std::endl << "||||||||||||||||||||||||" << std::endl;
    return 0;
}
