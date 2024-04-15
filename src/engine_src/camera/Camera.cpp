#include "Camera.hpp"

#include <iostream>

const glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);

BaseCamera::BaseCamera() {
    position = glm::vec3(0.0f, 0.0f,  3.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = WORLD_UP;
    right = glm::normalize(glm::cross(front, up));
    yaw = -90.0f;
    pitch = 0.0f;
}

void BaseCamera::update() {
    view = glm::lookAt(position, position + front, up);
}