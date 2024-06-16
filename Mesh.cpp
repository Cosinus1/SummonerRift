#include "Mesh.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <glm/glm.hpp>


//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
Mesh::Mesh() : mLoaded(false) {}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
Mesh::~Mesh() {
    for (auto& subMesh : mSubMeshes) {
        glDeleteVertexArrays(1, &subMesh.VAO);
        glDeleteBuffers(1, &subMesh.VBO);
    }
}

//-----------------------------------------------------------------------------
// Get SubMeshes
//-----------------------------------------------------------------------------
std::vector<SubMesh>& Mesh::getSubMeshes() {
    return mSubMeshes;
}

//-----------------------------------------------------------------------------
// invert normals
//-----------------------------------------------------------------------------
void Mesh::invertNormals() {
    for (auto& subMesh : mSubMeshes) {
        for (auto& vertex : subMesh.vertices) {
            // Invert the direction of the normals
            vertex.normal = -vertex.normal;
        }
        // Update the buffers with the new normals
        glBindBuffer(GL_ARRAY_BUFFER, subMesh.VBO);
        glBufferData(GL_ARRAY_BUFFER, subMesh.vertices.size() * sizeof(Vertex), &subMesh.vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

//-----------------------------------------------------------------------------
// Rotate textures
//-----------------------------------------------------------------------------

void SubMesh::rotateTextureX(float angleDegrees) {
    // Convert angle from degrees to radians
    float angleRadians = glm::radians(angleDegrees);

    // Calculate sin and cos of the angle for rotation
    float cosAngle = std::cos(angleRadians);
    float sinAngle = std::sin(angleRadians);
    for (auto& vertex : vertices) {

        // Rotate texture coordinates
        float oldU = vertex.texCoords.x;
        float oldV = vertex.texCoords.y;
        vertex.texCoords.x = oldU * cosAngle - oldV * sinAngle;
        vertex.texCoords.y = oldU * sinAngle + oldV * cosAngle;

    }
    // Update the buffers with the new texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SubMesh::rotateTextureY(float angleDegrees) {
    // Convert angle from degrees to radians
    float angleRadians = glm::radians(angleDegrees);

    // Calculate sin and cos of the angle for rotation
    float cosAngle = std::cos(angleRadians);
    float sinAngle = std::sin(angleRadians);
    for (auto& vertex : vertices) {

        // Rotate texture coordinates
        float oldU = vertex.texCoords.x;
        float oldV = vertex.texCoords.y;
        vertex.texCoords.y = oldU * cosAngle - oldV * sinAngle;
        vertex.texCoords.x = oldU * sinAngle + oldV * cosAngle;

    }
    // Update the buffers with the new texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::rotateTexturesX(float angleDegrees){
    for (auto& subMesh : mSubMeshes) {
        subMesh.rotateTextureX(angleDegrees);
    }
}

void Mesh::rotateTexturesY(float angleDegrees){
    for (auto& subMesh : mSubMeshes) {
        subMesh.rotateTextureY(angleDegrees);
    }
}
//-----------------------------------------------------------------------------
// Helper function to split a string by a delimiter
//-----------------------------------------------------------------------------
std::vector<std::string> split(const std::string& s, const std::string& delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    size_t start = 0, end = 0;

    while ((end = s.find(delimiter, start)) != std::string::npos) {
        tokens.push_back(s.substr(start, end - start));
        start = end + delimiter.length();
    }
    tokens.push_back(s.substr(start));
    return tokens;
}
//-----------------------------------------------------------------------------
// Create the Object with the Textures
//-----------------------------------------------------------------------------
bool Mesh::createObject(const std::string&nameOBJ , bool invertUV) {
    // Load the OBJ file
    if (!loadOBJ(nameOBJ, invertUV)) {
        std::cerr << "Failed to load OBJ file" << std::endl;
        return false;
    } else std::cout << "OBJ file loaded" << std::endl;
    //Invert the normals
    invertNormals();
    // Load the Textures from MTL file
    if (!LoadTexturesFromMTL("models/" + MTLfilename)) {
        std::cerr << "Failed to load MTL file" << std::endl;
        return false;
    } else std::cout << "MTL file loaded" << std::endl;
    return true;
}
//-----------------------------------------------------------------------------
// Loads a Wavefront OBJ model
//-----------------------------------------------------------------------------

bool Mesh::loadOBJ(const std::string& filename, bool invertUV) {
    // Construct the full path with the ".obj" extension
    std::string fullPath = "models/" + filename + ".obj";

    // Open the OBJ file for reading
    std::ifstream fin(fullPath, std::ios::in);
    if (!fin) {
        std::cerr << "Cannot open " << fullPath << std::endl;
        return false;
    }

    std::cout << "Loading OBJ file " << filename << " ..." << std::endl;

    // Temporary variables to store each line and command
    std::string lineBuffer;
    std::vector<glm::vec3> tempVertices, tempNormals;
    std::vector<glm::vec2> tempUVs;
    Material material;
    std::string MTLname;
    glm::mat4 model(1.0f);

    // Init first subMesh
    SubMesh subMesh;
    subMesh.model = model;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<GLuint> uvIndices;

    while (std::getline(fin, lineBuffer)) {
        std::stringstream ss(lineBuffer);
        std::string cmd;
        ss >> cmd;

        // Store vertices information for the submesh
        if (cmd == "v") {
            glm::vec3 vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;
            tempVertices.push_back(vertex);
        } else if (cmd == "vn") {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            tempNormals.push_back(normal);
        } else if (cmd == "vt") {
            glm::vec2 uv;
            ss >> uv.x >> uv.y;
            if(invertUV) uv.y = -uv.y;
            tempUVs.push_back(uv);
        } else if (cmd == "f") {
            std::string faceData;
            std::vector<unsigned int> faceIndices;
            std::vector<unsigned int> faceUVIndices;
            std::vector<unsigned int> faceNormalIndices;

            while (ss >> faceData) {
                std::vector<std::string> data = split(faceData, "/");
                std::cout << data.size() <<std::endl;
                if (data.size() > 0 && !data[0].empty()) {
                    unsigned int vertexIndex = std::stoi(data[0]) - 1;
                    faceIndices.push_back(vertexIndex);
                }

                if (data.size() > 1 && !data[1].empty()) {
                    unsigned int uvIndex = std::stoi(data[1]) - 1;
                    faceUVIndices.push_back(uvIndex);
                } else {
                    std::cout << "Warning: Missing UV index for face." << std::endl;
                    unsigned int uvIndex = 0;
                    faceUVIndices.push_back(uvIndex); // Default UV index if missing
                }

                if (data.size() > 2 && !data[2].empty()) {
                    unsigned int normalIndex = std::stoi(data[2]) - 1;
                    faceNormalIndices.push_back(normalIndex);
                }
            }
            // Create vertices for each face
            for (size_t i = 0; i < faceIndices.size(); ++i) {
                Vertex vertex;
                vertex.position = tempVertices[faceIndices[i]];
                vertex.texCoords = tempUVs[faceUVIndices[i]];
                vertex.normal = tempNormals[faceNormalIndices[i]];
                vertices.push_back(vertex);
                indices.push_back(static_cast<GLuint>(vertices.size() - 1));
            }
        } else if (cmd == "usemtl") {
            // Store the texture file name in the submesh
            ss >> subMesh.textureName;
        } else if (cmd == "o") {
            // Store the vertex and index information in the submesh if not empty
            if (!vertices.empty()) {
                subMesh.vertices = vertices;
                subMesh.indices = indices;
                subMesh.initBuffers();
                mSubMeshes.push_back(subMesh);
                // Clear vectors for the next submesh
                vertices.clear();
                indices.clear();
                // Initialize a new submesh
                subMesh = SubMesh();
                subMesh.model = model;
            }
        }else if (cmd == "mtllib"){
            //Store the MTL name for later usage
            ss >> MTLfilename;
        }
    }

    // Push back the last submesh if not empty
    if (!vertices.empty()) {
        subMesh.vertices = vertices;
        subMesh.indices = indices;
        subMesh.initBuffers();
        mSubMeshes.push_back(subMesh);
    }

    fin.close();
    return (mLoaded = true);
}
//-----------------------------------------------------------------------------
// Load textures from .mtl file
//---------------------------------------------------------------------------------------
bool Mesh::LoadTexturesFromMTL(const std::string& mtlFilePath) {
    std::ifstream mtlFile(mtlFilePath);
    if (!mtlFile.is_open()) {
        std::cerr << "Failed to open MTL file: " << mtlFilePath << std::endl;
        return false;
    }

    std::string line;
    std::shared_ptr<Texture2D> currentTexture = nullptr;
    bool isTextureLoaded = false;
    bool isBlockFinished = false;
    std::string textureName;

    while (getline(mtlFile, line)) {
        std::stringstream ss(line);
        std::string token;
        ss >> token;

        // Get new MTL & init texture
        if (token == "newmtl") {
            ss >> textureName;
            currentTexture = std::make_shared<Texture2D>();
            isTextureLoaded = false;
        }
        // Get Material Informations
        else if (token == "Ns") {
            ss >> currentTexture->mMaterial.shininess;
        } else if (token == "Ni") {
            ss >> currentTexture->mMaterial.density;
        } else if (token == "Ka") {
            ss >> currentTexture->mMaterial.ambient.r >> currentTexture->mMaterial.ambient.g >> currentTexture->mMaterial.ambient.b;
        } else if (token == "Kd") {
            ss >> currentTexture->mMaterial.diffuse.r >> currentTexture->mMaterial.diffuse.g >> currentTexture->mMaterial.diffuse.b;
        } else if (token == "Ks") {
            ss >> currentTexture->mMaterial.specular.r >> currentTexture->mMaterial.specular.g >> currentTexture->mMaterial.specular.b;
        }
        // Get Texture Name
        else if (token == "map_Kd") {
            std::string textureFileName;
            ss >> textureFileName;
            if (currentTexture->loadTexture(textureFileName)) {
                textures[textureName] = currentTexture;
                isTextureLoaded = true;
            }
        }
        // If no texture found at the end of a block, try loading with textureName
        else if (token == " ") {
            if (!isTextureLoaded) {
                if (!currentTexture->loadTexture(textureName + ".png")) {
                    std::cerr << "Failed to load texture png : " << textureName << std::endl;
                }else if (!currentTexture->loadTexture(textureName + ".jpg")) {
                    std::cerr << "Failed to load texture jpg : " << textureName << std::endl;
                }else {
                    textures[textureName] = currentTexture;
                }
            }
            // Reset texture loaded flag for the next block
            isTextureLoaded = false;
        }
    }
    // Check if the last block did not contain a texture
    if (!isTextureLoaded) {
        if (!currentTexture->loadTexture(textureName + ".png")) {
            std::cerr << "Failed to load texture : " << textureName << std::endl;
        } else if (!currentTexture->loadTexture(textureName + ".jpg")) {
            std::cerr << "Failed to load texture jpg : " << textureName << std::endl;
        }else {
            textures[textureName] = currentTexture;
        }
    }

    mtlFile.close();
    return true;
}

//-----------------------------------------------------------------------------
// Create and initialize the vertex buffer and vertex array object for SubMesh
//-----------------------------------------------------------------------------
void SubMesh::initBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}

//-----------------------------------------------------------------------------
// Render the OBJ
//-----------------------------------------------------------------------------
void Mesh::draw() {
    if (!mLoaded) return;

    for (auto& subMesh : mSubMeshes) {

 
        subMesh.draw();


    }
}

//-----------------------------------------------------------------------------
// Render the mesh of the OBJ
//-----------------------------------------------------------------------------
void SubMesh::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}
