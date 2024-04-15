#pragma once

#include <string>
#include <filesystem>
#include <vector>

#include "../texture/Texture.hpp"

namespace fs = std::filesystem;

class Shader
{
private:
    unsigned int _fragmentShader;
    unsigned int _vertexShader;
    std::vector<Texture> _textures;

    unsigned int _compileShader(std::string source, unsigned int type);
    std::string _readFile(fs::path path);
public:
    unsigned int id;
    Shader(std::string shaderFolder);
    
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;
    void addTexture(Texture texture);
    
    void use();
};
