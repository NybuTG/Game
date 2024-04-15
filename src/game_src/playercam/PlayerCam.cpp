#include "PlayerCam.hpp"
#include <iostream>

PlayerCam::PlayerCam() 
{
    // using BaseCamera::BaseCamera;
    // BaseCamera();
    // std::cout << position.x << position.y << position.z << std::endl;
}

void PlayerCam::handleInput(GLFWwindow* window, float deltaTime) 
{
    float velocity = 1.1 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += front * velocity;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= front * velocity;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= right * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += right * velocity;
}

void PlayerCam::handleMouse(float xoffset, float yoffset) 
{

    yaw += xoffset * 0.5;
    pitch += yoffset * 0.5;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f ) {
        pitch = -89.0f;
    }

    glm::vec3 _front;
    _front.x = cos(glm::radians(yaw) * cos(glm::radians(pitch)));
    _front.y = sin(glm::radians(pitch));
    _front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(_front);
    right = glm::normalize(glm::cross(front, WORLD_UP));
    up = glm::normalize(glm::cross(right, front));
}

void PlayerCam::onlyHere() {
    std::cout << "this works" << std::endl;
}