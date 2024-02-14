#pragma once
#include "Utils.h"

class Cube {
public:
    float acceleration = 0.1f;
    float damper = 10;
    float speed = acceleration / damper;
    
    Cube();

    // vertices = x, y, z
    GLfloat vertices[12] = {
         -0.5f,  .5f, 0.0f,  // Top left vertex
        -0.5f, -0.5f, 0.0f,  // Bottom-left vertex
         0.5f, -.5f, 0.0f,   // Bottom-right vertex
         0.5f, .5f, 0.0f     // top right vertex
    };

    GLint VertCount = sizeof(vertices) / sizeof(vertices[0]);

    Transform transform;

    void Draw();

    void Fire();

    void updateVertexPositionsUp();

    void updateVertexPositionsDown();

    void updateVertexPositionsLeft();

    void updateVertexPositionsRight();

    void ScalePlayer(float factor);

    void AlignPlayer();

    void Initialize();
private:
    GLuint ShaderProgram,
        VertexBuffer,
        VertexArray,
        ShaderFragment,
        ShaderVertex;

    void InitializeVertexArrays();
};