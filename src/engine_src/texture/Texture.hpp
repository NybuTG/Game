#pragma once

#include <filesystem>

#include <glad/glad.h>

namespace fs = std::filesystem;


class Texture {
    public:
        std::string name;
        unsigned int id;

        Texture(std::string uniform_name, std::string img_file, int format, int wrap, int filter);
};