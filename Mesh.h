#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include <map>
#include <memory>

#define GLEW_STATIC
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "Material.h"
#include "Texture2D.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 color;
};

struct SubMesh {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    GLuint VBO, VAO;
    std::string textureName;
    int textureID;
    bool hasTexture = false;
    glm::mat4 model;

    void rotateTextureX(float angleDegrees);
    void rotateTextureY(float angleDegrees);
    void initBuffers();
    void setupVertexAttributes();
    void draw();
};

class Mesh {
public:
    Mesh();
    ~Mesh();

    //Functions
    void rotateTexturesX(float angleDegrees);
    void rotateTexturesY(float angleDegrees);
    void invertNormals();
    std::vector<SubMesh>& getSubMeshes();
    bool createObject(const std::string&nameOBJ , bool invertUV);
    bool loadOBJ(const std::string& filename, bool invertUV);
    bool LoadTexturesFromMTL(const string& mtlFilePath);
    void draw();
    void initBuffers();
    void setModelMatrix(const glm::mat4& matrix) {
        modelMatrix = matrix;
    }
    glm::mat4 getModelMatrix() {
        return modelMatrix;
    }

    //Texture map
    std::map<std::string, std::shared_ptr<Texture2D>> textures;
    //MTL file name 
    std::string MTLfilename;
private:
    bool mLoaded;
    std::vector<SubMesh> mSubMeshes;
    std::vector<Vertex> mVertices; 
    GLuint mVAO; 
    GLuint mVBO;
    glm::mat4 modelMatrix;
};

#endif // MESH_H
