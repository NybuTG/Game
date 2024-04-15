#include "Shader.hpp"

#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream> 
#include <string>

const fs::path SHADER_PATH = fs::path(std::string(ROOT).append("/assets/shaders/"));

Shader::Shader(std::string shaderFolder) 
{
    // Create fragment and vertex shader paths
    fs::path vs_path = fs::path(SHADER_PATH) += fs::path(shaderFolder) += fs::path("/") += "shader.vs";
    fs::path fs_path = fs::path(SHADER_PATH) += fs::path(shaderFolder) += fs::path("/") += "shader.fs";

    // Read the files
    std::string vertexSource = _readFile(vs_path);
    std::string fragmentSource = _readFile(fs_path);

    // Compile
    // TODO :: Vertexshader seems to think it fails, despite working
    _vertexShader = _compileShader(vertexSource, GL_VERTEX_SHADER);
    _fragmentShader = _compileShader(fragmentSource, GL_FRAGMENT_SHADER);

    // Attach and compile shader program
    id = glCreateProgram();
    glAttachShader(id, _vertexShader);
    glAttachShader(id, _fragmentShader);
    glLinkProgram(id);

    // Check for status of shader compile
    int  sha_success;
    char sha_infoLog[512];
    glGetProgramiv(id, GL_LINK_STATUS, &sha_success);
    if(!sha_success) {
        glGetProgramInfoLog(id, 512, NULL, sha_infoLog);
        std::cout << "ERROR shader failed compiling :: " << sha_infoLog << std::endl;
    }
    
    glDeleteShader(_vertexShader);
    glDeleteShader(_fragmentShader);

}

unsigned int Shader::_compileShader(std::string source, unsigned int type) {
    const char* source_str = source.c_str();
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source_str, NULL);
    glCompileShader(shader);

    int  success;
    char infoLog[512];
    glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(_vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR :: Shader compilation failed :: " << std::hex << "0x" << type << std::dec << " :: " << infoLog << std::endl;
    }

    return shader;
}

// Helper function for reading file, roughly based on the code from learnopengl.com
std::string Shader::_readFile(fs::path path)
{   
    std::ifstream file;
    std::string output;

    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
        file.open(path);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        output = stream.str();
    } catch(std::ifstream::failure e) {
        std::cout << "ERROR: Could not read file :: " << path << std::endl;
    }

    return output;
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);   
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}
void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
}

void Shader::addTexture(Texture texture) {

    // cursed but works, only runs when loading anyway
    use();
    setInt(texture.name, _textures.size());
    _textures.push_back(texture);
    
}


void Shader::use() 
{ 
    glUseProgram(id);

    // If there are any textures, bind each texture and set the right uniform
    // Based on tex class which has both the name (Uniform Name) and the ID
    if (!(_textures.empty())) {
        for (int i; i < _textures.size(); i++) {

            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, _textures[i].id);
        }
    }
} 