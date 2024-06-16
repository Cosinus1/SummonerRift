// Texture2D.h

#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#define GLEW_STATIC
#include "GL/glew.h"
#include <string>
#include <vector>
#include <map>       
#include <memory>    
#include "Material.h"
using std::string;
using std::vector;

class Texture2D
{
public:
    Texture2D();
    virtual ~Texture2D();
    Texture2D(const Texture2D& rhs) {}

    // Variables
    GLuint mTexture;
    Material mMaterial;

    // Functions
    bool loadTexture(const string& folderName = "", bool generateMipMaps = true);
    bool loadMTLV0(const std::string& fileName, size_t index);
    void bind(GLuint texUnit = 0);
    void unbind(GLuint texUnit = 0);

private:
    Texture2D& operator=(const Texture2D& rhs) = delete;
};

#endif // TEXTURE2D_H
