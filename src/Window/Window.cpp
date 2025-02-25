#include "Window.h"

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <glm/vec2.hpp>

namespace Window {

    glm::ivec2 Window::m_WindowSize;

    Window::Window(glm::ivec2 WindowSize, const char* title){

        m_WindowSize = WindowSize;

        if (!glfwInit())
        {
            std::cout << "Error while loading GLFW..." << std::endl;
            return;
        }

        p_Window = glfwCreateWindow(WindowSize.x, WindowSize.y, title, nullptr, nullptr);
        if (!p_Window)
        {
            glfwTerminate();
            std::cout << "Failed to create window..." << std::endl;
            return;
        }

        glfwSetWindowSizeCallback(p_Window, glfwWindowResizedCallback);
        glfwSetKeyCallback(p_Window, glfwPressedEscapeCallback);

        glfwMakeContextCurrent(p_Window);

        if (!gladLoadGL())
        {
            std::cout << "Error while loading GLAD..." << std::endl;
            return;
        }

        glClearColor(0, 1, 1, 1);
    }

    void Window::glfwWindowResizedCallback(GLFWwindow* p_Window, int width, int height)
    {
        m_WindowSize.x = width;
        m_WindowSize.y = height;

        glViewport(0, 0, width, height);
    }

    void Window::glfwPressedEscapeCallback(GLFWwindow* p_Window, int key, int scancode, int action, int mode)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(p_Window, true);
        }
    }
}


