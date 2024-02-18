#pragma once
#include "Utils.h"


class Cube {
public:
    float acceleration = 1.0f;
    float damper = 10;
    float speed = acceleration / damper;
    std::string TexturePath = "Artwork/Player.png";
    const char* CubeFriendlyName = "Player_Cube";
    bool UseTextures = true;
    
    Cube();
    ~Cube();

    Shader CubeShader;

    float vertices[20] = {
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
    };

    unsigned int indices[6] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
    };

    GLint VertCount = sizeof(vertices) / sizeof(vertices[0]);
    GLint IndicesCount = sizeof(indices) / sizeof(indices[0]);

    glm::mat4 ModelMatrix = glm::mat4(1.0f);

    void Draw();

    void Fire();

    void updateVertexPositionsUp();

    void updateVertexPositionsDown();

    void updateVertexPositionsLeft();

    void updateVertexPositionsRight();

    void ScalePlayer(float factor, GLuint& ProgramShader);

    void AlignPlayer();

    void Initialize();
private:
    GLuint 
        VertexBuffer,
        VertexArray,
        ShaderFragment,
        ShaderVertex,
        EBO,
        Texture;

    

    void InitializeGeometry();

    void UpdateVertexBuffer();
};