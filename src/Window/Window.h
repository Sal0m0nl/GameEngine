#pragma once
#include "glm/vec2.hpp"

class GLFWwindow;



namespace Window {
    class Window {
    public:

        Window(glm::ivec2 WindowSize, const char* title);
        ~Window() = default;
        GLFWwindow* getWindow() const { return p_Window; };

        static void glfwPressedEscapeCallback(GLFWwindow* p_Window, int key, int scancode, int action, int mode);
        static void glfwWindowResizedCallback(GLFWwindow *p_Window, int width, int height);

        static glm::ivec2 m_WindowSize;
    private:
        GLFWwindow* p_Window;

    };
}
