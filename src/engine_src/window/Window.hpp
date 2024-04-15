#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../camera/Camera.hpp"
#include "../../game_src/game/Game.hpp"

class Window 
{
private:       
    GLFWwindow *_window;
    // void processInput(GLFWwindow *window);
    void _handleInput();
    static void _framebuffer_size_callback(GLFWwindow* gl_window, int width, int height);
    static void _mouse_callback(GLFWwindow* window, double xpos, double ypos);
    double _start=0;
    // Camera _myCamera;
public:
    double deltaTime;
    Window(GLFWwindow *window);
    void start();
};