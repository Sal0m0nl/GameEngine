#include <GLFW/glfw3.h>

int main(void)
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

    while (!glfwWindowShouldClose(p_Window))
    {
        glfwSwapBuffers(p_Window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}