#pragma once

#include "../../engine_src/camera/Camera.hpp"

const glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);

class PlayerCam : public BaseCamera {
    public:
        
        PlayerCam();
        void handleInput(GLFWwindow* window, float deltaTime);
        void handleMouse(float xoffset, float yoffset);
        void onlyHere();
};