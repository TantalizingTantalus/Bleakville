#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Utils.h"

class Cube {
public:
    float speed = 0.1f / 10;
    // Set up vertex data and attribute pointers
    // vertices = x, y, z
    GLfloat vertices[12] = {
         -0.5f,  .5f, 0.0f,  // Top left vertex
        -0.5f, -0.5f, 0.0f,  // Bottom-left vertex
         0.5f, -.5f, 0.0f,   // Bottom-right vertex
         0.5f, .5f, 0.0f     // top right vertex
    };
    int VertCount = sizeof(vertices) / sizeof(vertices[0]);

    Position position;

    Position GetPosition()
    {
        position.x = abs(vertices[3]) - abs(vertices[6]);
        position.y = abs(vertices[1]) - abs(vertices[7]);

        return position;
    }

    void Fire();

    void updateVertexPositionsUp();

    void updateVertexPositionsDown();

    void updateVertexPositionsLeft();

    void updateVertexPositionsRight();

    void ScalePlayer(float factor);

    void AlignPlayer();
};