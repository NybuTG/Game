#pragma once

#include <vector>

#include "../shader/Shader.hpp"

class GameObject 
{
    public:
        GameObject() {};
        virtual void update() {};
};

class RenderObject : public GameObject
{
    private:
        float[] _vertices;
        void _render() {};
    public:
        // TODO: Input shader, images etc.
        RenderObject() {};
}