#include "Window.hpp"


#include <filesystem>
#include <iostream>
#include <fmt/core.h>

namespace fs = std::filesystem;

#include "../shader/Shader.hpp"
#include "../texture/Texture.hpp"
#include "../camera/Camera.hpp"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Game myGame = Game();

void Window::_framebuffer_size_callback(GLFWwindow* gl_window, int width, int height)
{
  glViewport(0, 0, width, height);
}

// void Window::_handleInput()
// {
//     if(glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(_window, true);

//     _myCamera.handleInput(_window);
// }


// Camera* globalCamera;
float lastX = 400;
float lastY = 300;

void Window::_mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{   
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    myGame.handleMouse(xoffset, yoffset);
}


void Window::start() {

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);  
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);




    std::cout << "INFO :: Starting texture load" << std::endl;

    Texture texture1 = Texture("texture1", "container.jpg", GL_RGB, GL_REPEAT, GL_NEAREST);
    Texture texture2 = Texture("texture2", "awesomeface.png", GL_RGBA, GL_REPEAT, GL_NEAREST);

    std::cout << "INFO :: Starting shader load" << std::endl;

    Shader myShader = Shader("myShader");
    myShader.addTexture(texture1);
    myShader.addTexture(texture2);


    // Model matrix, makes the model centered at 0,0,0
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 

    glm::mat4 view = glm::mat4(1.0f);
    // // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    

    glEnable(GL_DEPTH_TEST);  
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(_window, _mouse_callback);  

    while (!glfwWindowShouldClose(_window))
    {   
        myGame.deltaTime = glfwGetTime() - _start;
        _start = glfwGetTime();

        std::string title = fmt::format("My OpenGL Window! - {:.3f}", (float)myGame.deltaTime);
        glfwSetWindowTitle(_window, title.c_str());
        myGame.handleInput();
    
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // _myCamera.update();
        // std::cout << glm::value_ptr(_myCamera.view) << std::endl;
        
        myGame.update();


        model = glm::rotate(model, (float)deltaTime * glm::radians(500.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        myShader.use();

        glUniformMatrix4fv(glGetUniformLocation(myShader.id, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(myShader.id, "view"), 1, GL_FALSE, glm::value_ptr(myGame.getCamera()->view));
        // glUniformMatrix4fv(glGetUniformLocation(myShader.id, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(myShader.id, "projection"), 1, GL_FALSE, glm::value_ptr(projection));


        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        glfwSwapBuffers(_window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

Window::Window(GLFWwindow *window) {
    _window = window;
    myGame.setWindow(window);
    // _myCamera = Camera();
    // _myCamera.id = 1230;
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(_window, _framebuffer_size_callback);
}


