#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
    if (!glfwInit())
        return -1;

    GLFWwindow* p_Window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!p_Window)
    {
        glfwTerminate();
        return -1;
    }

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