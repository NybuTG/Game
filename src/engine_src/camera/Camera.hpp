#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

class BaseCamera {

public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::mat4 view;

    float pitch;
    float yaw;

    unsigned int id;
    
    BaseCamera();
    void update();
    virtual void handleInput(GLFWwindow *window, float deltaTime) {};
    virtual void handleMouse(float xoffset, float yoffset) {};
    // glm::mat4 viewMatrix();
};