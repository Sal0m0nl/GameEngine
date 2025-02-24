#pragma once
#include <string>

class GLFWwindow;


namespace Window {
    class Window {
    public:

        Window(int width, int height, const char* title);
        ~Window() = default;
        GLFWwindow* getWindow() const { return p_Window; };

        static void glfwPressedEscapeCallback(GLFWwindow* p_Window, int key, int scancode, int action, int mode);
        static void glfwWindowResizedCallback(GLFWwindow *p_Window, int width, int height);
    private:
        GLFWwindow* p_Window;
    };
}
