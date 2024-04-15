#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "engine_src/window/Window.hpp"
// #include "shader/Shader.hpp"

int main() 
{
    // Setup GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* gl_window = glfwCreateWindow(800, 600, "My OpenGL Window", NULL, NULL);
    if (gl_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(gl_window);

    // Setup GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Window myWindow = Window(gl_window);


    // This starts game and wont quit until user ends program
    myWindow.start();

    return 0;
}

