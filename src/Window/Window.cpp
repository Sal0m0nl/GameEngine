#include "Window.h"

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Window {

    Window::Window(int width, int height, const char* title){
        if (!glfwInit())
        {
            std::cout << "Error while loading GLFW..." << std::endl;
            return;
        }

        p_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
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

        glClearColor(1, 0, 1, 1);
    }

    void Window::glfwWindowResizedCallback(GLFWwindow* p_Window, int width, int height)
    {
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


