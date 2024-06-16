#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#define GLEW_STATIC
#include "GL/glew.h"    // Important - this header must come before glfw3 header
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Camera.h"
#include "Mesh.h"

// Global Variables
const char* APP_TITLE = "Projet OpenGL : Summoner's Rift - ";
int gWindowWidth = 1024;
int gWindowHeight = 768;
GLFWwindow* gWindow = NULL;
bool gWireframe = false;
glm::vec4 gClearColor(0.23f, 0.38f, 0.47f, 1.0f);

FPSCamera fpsCamera(glm::vec3(0.0f, 2.0f, 10.0f));
const double ZOOM_SENSITIVITY = -3.0;
const float MOVE_SPEED = 5.0; // units per second
const float MOUSE_SENSITIVITY = 0.1f;

// Function prototypes
void alignEyeWithCamera(Mesh& eyeMesh, const glm::vec3& eyePos, const glm::vec3& cameraPos);
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
void glfw_onFramebufferSize(GLFWwindow* window, int width, int height);
void glfw_onMouseScroll(GLFWwindow* window, double deltaX, double deltaY);
void update(double elapsedTime, glm::vec3 modelPos);
void showFPS(GLFWwindow* window);
bool initOpenGL();

//-----------------------------------------------------------------------------
// Main Application Entry Point
//-----------------------------------------------------------------------------
int main()
{
    if (!initOpenGL())
    {
        std::cerr << "GLFW initialization failed" << std::endl;
        return -1;
    }

    ShaderProgram lightingShader;
    lightingShader.loadShaders("shaders/lighting_dir.vert", "shaders/lighting_dir.frag");

    // Load OBJ and Textures
    //Darius
    Mesh dariusMesh;
    dariusMesh.createObject("darius", false);

    //Aatrox
    Mesh aatroxMesh;
    aatroxMesh.createObject("aatrox", true);

    //Summoner Rift
    Mesh riftMesh;
    riftMesh.createObject("summoner_rift", true);

    //ashbringer
    Mesh ashMesh;
    ashMesh.createObject("ashbringer", true);

    //eye
    Mesh eyeMesh;
    eyeMesh.createObject("eye", false);

    //Craftsman
    Mesh craftMesh;
    craftMesh.createObject("craftsman", false);

    //Skull 
    Mesh skullMesh;
    skullMesh.createObject("skull", false);

    // Put all Meshes in an array
    Mesh meshes[] =
    {  dariusMesh,
        aatroxMesh, 
        riftMesh, 
        eyeMesh,
        craftMesh,
        skullMesh 
    };

    // Model positions of each mesh 
    glm::vec3 modelPos[] = {
        glm::vec3(0.0f, -14.0f, 10.0f), //Darius
        glm::vec3(0.0f, -12.0f, 4.0f),//Aatrox
        glm::vec3(0.0f, -100.0f, 0.0f),//Rift
        glm::vec3(0.0f, 0.0f, 00.0f),//Eye
        glm::vec3(0.0f, -10.0f, 0.0f),//Craftsman
        glm::vec3(0.0f, 0.0f, 0.0f),//Skull
    };
    
    // Model scales of each mesh 
    glm::vec3 modelScale[] = {
        glm::vec3(0.01f, 0.01f, 0.01f),//Darius
        glm::vec3(0.01f, 0.01f, 0.01f),//Aatrox
        glm::vec3(5.0f, 5.0f, 5.0f),//Rift
        glm::vec3(70.0f, 70.0f, 70.0f),//Eye
        glm::vec3(1.0f, 1.0f, 1.0f)//Skull
    };

    double lastTime = glfwGetTime();
    float angle = 180.0f;
    float rotAngle = 10.0f;

    // Rendering loop
    while (!glfwWindowShouldClose(gWindow))
    {
        // Show FPS
        showFPS(gWindow);

        // Time calculation
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // Poll for and process events
        glfwPollEvents();
        update(deltaTime, modelPos[0]);

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set up transformations
        glm::mat4 view = fpsCamera.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(fpsCamera.getFOV()), (float)gWindowWidth / (float)gWindowHeight, 0.1f, 200.0f);

        // Use the lighting shader
        lightingShader.use();
        lightingShader.setUniform("view", view);
        lightingShader.setUniform("projection", projection);
        lightingShader.setUniform("viewPos", fpsCamera.getPosition());

        // Set the first light properties
        lightingShader.setUniform("dirLight1.direction", glm::vec3(0.0f, -0.9f, -0.17f));
        lightingShader.setUniform("dirLight1.ambient", glm::vec3(0.4f, 0.4f, 0.4f));
        lightingShader.setUniform("dirLight1.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setUniform("dirLight1.specular", glm::vec3(1.0f, 1.0f, 1.0f));

        // Set the second light properties
        lightingShader.setUniform("dirLight2.direction", glm::vec3(0.5f, -0.5f, -0.5f));
        lightingShader.setUniform("dirLight2.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
        lightingShader.setUniform("dirLight2.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
        lightingShader.setUniform("dirLight2.specular", glm::vec3(0.8f, 0.8f, 0.8f));

        // Align the eye mesh with the camera
        alignEyeWithCamera(eyeMesh, modelPos[4], fpsCamera.getPosition());

        //------------------------------------------------------------------------------------------------
        //                                          Mesh Rendering
        //------------------------------------------------------------------------------------------------
        //iterate over all the meshes in the array
        int i = 0;
        for (auto& mesh : meshes) {
            // Iterate over all the submeshes in the mesh
            for (auto& subMesh : mesh.getSubMeshes()) {
                // Get the corresponding texture name for the submesh
                std::string textureFileName = subMesh.textureName;

                // Find the texture in the mesh's texture map
                auto it = mesh.textures.find(textureFileName);
                
                if (it != mesh.textures.end()) {
                    // Get the texture
                    std::shared_ptr<Texture2D> texture = it->second;

                    if(texture){
                        // Set material properties in the shader
                        lightingShader.setUniform("material.shininess", texture->mMaterial.shininess);
                        lightingShader.setUniform("material.ambient", texture->mMaterial.ambient);
                        lightingShader.setUniform("material.diffuse", texture->mMaterial.diffuse);
                        lightingShader.setUniform("material.specular", texture->mMaterial.specular);
                    }
                    // Bind the texture
                    texture->bind();
                } else {
                    // Set default material properties in the shader if no texture is found
                    std::cout << "no Material Properties found for : " + subMesh.textureName << std::endl;
                    lightingShader.setUniform("material.shininess", 2.0f); // Default shininess
                    lightingShader.setUniform("material.ambient", glm::vec3(0.2f, 0.2f, 0.2f)); // Default ambient color
                    lightingShader.setUniform("material.diffuse", glm::vec3(0.8f, 0.8f, 0.8f)); // Default diffuse color
                    lightingShader.setUniform("material.specular", glm::vec3(1.0f, 1.0f, 1.0f)); // Default specular color
                }

                // Calculate basic model transformation for each submesh
                glm::mat4 modelSubMesh = glm::translate(glm::mat4(1.0f), modelPos[i]);
                
                // Apply rotation if it's the Darius mesh
                if (i == 0) {
                    modelSubMesh = glm::rotate(modelSubMesh, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around the Y-axis
                }
                // Alif (i == 4) {
                //     alignEyeWithCamera(mesh, modelPos[4], fpsCamera.getPosition());
                //     modelSubMesh = mesh.getModelMatrix();
                // }ign eye mesh with camera if it's the eyeMesh
                // if (i == 4) {
                //     alignEyeWithCamera(mesh, modelPos[4], fpsCamera.getPosition());
                //     modelSubMesh = mesh.getModelMatrix();
                // }
                    // Scale model
                    modelSubMesh = glm::scale(modelSubMesh, modelScale[i]);


                lightingShader.setUniform("model", modelSubMesh);

                // Draw the submesh
                subMesh.draw();

                // Unbind the texture (if it was bound)
                if (it != mesh.textures.end()) {
                    it->second->unbind();
                }
            }
            // Update i for modelPos
            i++;
        }

        
        //---------------------------------------------------------------------------------------------------------
        // Swap front and back buffers
        glfwSwapBuffers(gWindow);

        lastTime = currentTime;
    }

    glfwTerminate();
    return 0;
}



//-----------------------------------------------------------------------------
// Initialize GLFW and OpenGL
//-----------------------------------------------------------------------------
bool initOpenGL()
{
    // Initialize GLFW 
    if (!glfwInit())
    {
        std::cerr << "GLFW initialization failed" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    gWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, APP_TITLE, NULL, NULL);
    if (gWindow == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(gWindow);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return false;
    }

    glfwSetKeyCallback(gWindow, glfw_onKey);
    glfwSetFramebufferSizeCallback(gWindow, glfw_onFramebufferSize);
    glfwSetScrollCallback(gWindow, glfw_onMouseScroll);

    glfwSetInputMode(gWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(gWindow, gWindowWidth / 2.0, gWindowHeight / 2.0);

    glClearColor(gClearColor.r, gClearColor.g, gClearColor.b, gClearColor.a);

    int w, h;
    glfwGetFramebufferSize(gWindow, &w, &h); // For retina display
    glViewport(0, 0, w, h);
    glEnable(GL_DEPTH_TEST);

    return true;
}

//-----------------------------------------------------------------------------
// Is called whenever a key is pressed/released via GLFW
//-----------------------------------------------------------------------------
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    
    if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
    {
        gWireframe = !gWireframe;
        if (gWireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

//-----------------------------------------------------------------------------
// Is called when the window is resized
//-----------------------------------------------------------------------------
void glfw_onFramebufferSize(GLFWwindow* window, int width, int height)
{
    gWindowWidth = width;
    gWindowHeight = height;

    int w, h;
    glfwGetFramebufferSize(gWindow, &w, &h); // For retina display
    glViewport(0, 0, w, h);
}

//-----------------------------------------------------------------------------
// Called by GLFW when the mouse wheel is rotated
//-----------------------------------------------------------------------------
void glfw_onMouseScroll(GLFWwindow* window, double deltaX, double deltaY)
{
    double fov = fpsCamera.getFOV() + deltaY * ZOOM_SENSITIVITY;
    fov = glm::clamp(fov, 1.0, 120.0);
    fpsCamera.setFOV((float)fov);
}

//-----------------------------------------------------------------------------
// Update stuff every frame
//-----------------------------------------------------------------------------
void update(double elapsedTime, glm::vec3 modelPos)
{
    double mouseX, mouseY;
    glfwGetCursorPos(gWindow, &mouseX, &mouseY);
    fpsCamera.rotate((float)(gWindowWidth / 2.0 - mouseX) * MOUSE_SENSITIVITY, (float)(gWindowHeight / 2.0 - mouseY) * MOUSE_SENSITIVITY);
    glfwSetCursorPos(gWindow, gWindowWidth / 2.0, gWindowHeight / 2.0);

    if (glfwGetKey(gWindow, GLFW_KEY_W) == GLFW_PRESS)
        fpsCamera.move(MOVE_SPEED * (float)elapsedTime * fpsCamera.getLook());
    else if (glfwGetKey(gWindow, GLFW_KEY_S) == GLFW_PRESS)
        fpsCamera.move(MOVE_SPEED * (float)elapsedTime * -fpsCamera.getLook());

    if (glfwGetKey(gWindow, GLFW_KEY_A) == GLFW_PRESS)
        fpsCamera.move(MOVE_SPEED * (float)elapsedTime * -fpsCamera.getRight());
    else if (glfwGetKey(gWindow, GLFW_KEY_D) == GLFW_PRESS)
        fpsCamera.move(MOVE_SPEED * (float)elapsedTime * fpsCamera.getRight());

    if (glfwGetKey(gWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
        fpsCamera.move(MOVE_SPEED * (float)elapsedTime * glm::vec3(0.0f, 1.0f, 0.0f));
    else if (glfwGetKey(gWindow, GLFW_KEY_X) == GLFW_PRESS)
        fpsCamera.move(MOVE_SPEED * (float)elapsedTime * -glm::vec3(0.0f, 1.0f, 0.0f));

    if (glfwGetKey(gWindow, GLFW_KEY_E) == GLFW_PRESS)
        fpsCamera.lookAt(modelPos);
}

//-----------------------------------------------------------------------------
// Code computes the average frames per second, and also the average time it takes
// to render one frame.  These stats are appended to the window caption bar.
//-----------------------------------------------------------------------------
void showFPS(GLFWwindow* window)
{
    static double previousSeconds = 0.0;
    static int frameCount = 0;
    double elapsedSeconds;
    double currentSeconds = glfwGetTime(); // returns number of seconds since GLFW started, as double float

    elapsedSeconds = currentSeconds - previousSeconds;

    // Limit text updates to 4 times per second
    if (elapsedSeconds > 0.25)
    {
        previousSeconds = currentSeconds;
        double fps = (double)frameCount / elapsedSeconds;
        double msPerFrame = 1000.0 / fps;

        std::ostringstream outs;
        outs.precision(3);
        outs << std::fixed
            << APP_TITLE << "    "
            << "FPS: " << fps << "    "
            << "Frame Time: " << msPerFrame << " (ms)";
        glfwSetWindowTitle(window, outs.str().c_str());

        frameCount = 0;
    }

    frameCount++;
}
//-----------------------------------------------------------------------------
// Align the eye with the camera
//-----------------------------------------------------------------------------
void alignEyeWithCamera(Mesh& eyeMesh, const glm::vec3& eyePos, const glm::vec3& cameraPos)
{
    glm::vec3 direction = glm::normalize(cameraPos - eyePos);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::normalize(glm::cross(up, direction));
    glm::vec3 newUp = glm::cross(direction, right);

    glm::mat4 rotationMatrix = glm::mat4(1.0f);
    rotationMatrix[0] = glm::vec4(right, 0.0f);
    rotationMatrix[1] = glm::vec4(newUp, 0.0f);
    rotationMatrix[2] = glm::vec4(direction, 0.0f);

    eyeMesh.setModelMatrix(rotationMatrix);
}
struct EyeRotation {
    float pitch;
    float yaw;
};

EyeRotation eyeRotation = {0.0f, 0.0f};

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    static bool firstMouse = true;
    static double lastX = xpos;
    static double lastY = ypos;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    double xOffset = xpos - lastX;
    double yOffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    eyeRotation.yaw += xOffset;
    eyeRotation.pitch += yOffset;

    // Clamp the pitch value to avoid flipping
    if (eyeRotation.pitch > 89.0f)
        eyeRotation.pitch = 89.0f;
    if (eyeRotation.pitch < -89.0f)
        eyeRotation.pitch = -89.0f;
}

