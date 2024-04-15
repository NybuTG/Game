#pragma once

#include <vector>
#include <memory>

#include "../../engine_src/camera/Camera.hpp"

using CamPtr = std::unique_ptr<BaseCamera>;

class Game {
    private:
        unsigned int _activeCamera;
        std::vector<std::unique_ptr<BaseCamera>> _cameras;
        GLFWwindow* _window;
    public:
        double deltaTime;

        Game();
        void setWindow(GLFWwindow* window);
        void update();
        void handleMouse(float xoffset, float yoffset);
        void handleInput();
        // Returns camera ID
        unsigned int addCamera(BaseCamera* camera);
        BaseCamera* setCamera(int camera_id);
        BaseCamera* getCamera();
};