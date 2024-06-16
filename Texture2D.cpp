#include "Texture2D.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <map>
#include "stb_image.h"

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
Texture2D::Texture2D() {}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
Texture2D::~Texture2D() {
    glDeleteTextures(1, &mTexture);
}

//-----------------------------------------------------------------------------
// Load a texture with a given filename using stb image loader
//     
// Creates mip maps if generateMipMaps is true.
//-----------------------------------------------------------------------------

bool Texture2D::loadTexture(const std::string& fileName, bool generateMipMaps)
{
    std::string fullPath = "textures/" + fileName;

    // Open the file to check if it exists
    std::ifstream file(fullPath);
    if (!file.good()) {
        return false;
    }
    file.close();

    // Load image data using stb_image
    int width, height, channels;
    unsigned char* imageData = stbi_load(fullPath.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    // Check if texture loading was successful
    if (imageData == nullptr) {
        std::cerr << "Error loading texture '" << fullPath << "': " << stbi_failure_reason() << std::endl;
        return false;
    }

    // Store image data in the OpenGL texture object
    glGenTextures(1, &mTexture);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    if (generateMipMaps) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // Free image data
    stbi_image_free(imageData);

    return true;
}

//-----------------------------------------------------------------------------
// Bind the texture unit passed in as the active texture in the shader
//-----------------------------------------------------------------------------
void Texture2D::bind(GLuint texUnit) {
    glActiveTexture(GL_TEXTURE0 + texUnit);
    glBindTexture(GL_TEXTURE_2D, mTexture);
}

//-----------------------------------------------------------------------------
// Unbind the texture unit passed in as the active texture in the shader
//-----------------------------------------------------------------------------
void Texture2D::unbind(GLuint texUnit) {
    glActiveTexture(GL_TEXTURE0 + texUnit);
    glBindTexture(GL_TEXTURE_2D, 0);
}
