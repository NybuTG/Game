#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const fs::path IMG_FOLDER = fs::path(std::string(ROOT).append("/assets/img/"));

Texture::Texture(std::string uniform_name, std::string img_file, int format, int wrap, int filter) {

    // Load Uniform name into class property:
    name = uniform_name;

    std::string img = std::string(fs::path(IMG_FOLDER) += img_file);

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

     // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis. 
    unsigned char *data = stbi_load(img.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "INFO :: Loaded texture :: " << img << std::endl;
    }
    else
    {
        std::cout << "ERROR :: Failed to load texture :: " << img << std::endl;
    }

    stbi_image_free(data);
}