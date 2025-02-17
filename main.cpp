#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int g_windowSizeX = 640;
int g_windowSizeY = 480;

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


int main()
{
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

    glClearColor(0, 1, 0, 1);

    while (!glfwWindowShouldClose(p_Window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(p_Window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
