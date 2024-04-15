#include "Game.hpp"
#include "../playercam/PlayerCam.hpp"

#include <iostream>
#include <typeinfo>

Game::Game() 
{
    // BaseCamera* playerCam = static_cast<BaseCamera*>(new PlayerCam());
    PlayerCam* playerCam = new PlayerCam();
    addCamera(playerCam);

    BaseCamera* secondCam = static_cast<BaseCamera*>(new PlayerCam());
    addCamera(secondCam);
    std::cout << typeid(playerCam).name() << std::endl;
    playerCam->onlyHere();
}


void Game::update()
{
    getCamera()->update();
}

void Game::handleMouse(float xoffset, float yoffset)
{
    getCamera()->handleMouse(xoffset, yoffset);
}

void Game::handleInput()
{
    getCamera()->handleInput(_window, deltaTime);
}


// Returns camera ID
unsigned int Game::addCamera(BaseCamera* camera)
{
    _cameras.emplace_back(std::move(camera));
    _activeCamera = _cameras.size() - 1;
    (*_cameras[_activeCamera]).id = 101;
    return _activeCamera;
}

BaseCamera* Game::setCamera(int camera_id)
{
    _activeCamera = camera_id;
    return _cameras[_activeCamera].get();
}

BaseCamera* Game::getCamera()
{
    return _cameras[_activeCamera].get();
}

void Game::setWindow(GLFWwindow* window) 
{
    _window = window;
}
