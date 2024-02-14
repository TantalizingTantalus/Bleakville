#include "Cube.h"

Cube::Cube()
{
    Logger::LogInformation("Player cube created!");
}

void Cube::updateVertexPositionsUp() {


    for (int i = 1; i < VertCount; i += 3)
    {
        vertices[i] += speed;
    }
}

void Cube::updateVertexPositionsDown() {

    for (int i = 1; i < VertCount; i += 3)
    {
        vertices[i] -= speed;
    }
}

void Cube::updateVertexPositionsLeft() {



    for (int i = 0; i < VertCount; i += 3)
    {
        vertices[i] -= speed;
    }

}

void Cube::updateVertexPositionsRight() {
    for (int i = 0; i < VertCount; i += 3)
    {
        vertices[i] += speed;
    }

}

void Cube::ScalePlayer(float factor)
{

    for (int i = 0; i < VertCount; ++i) {
        vertices[i] *= factor;
    }
}

void Cube::AlignPlayer()
{

    for (int i = 1; i < VertCount; i += 3)
    {
        vertices[i] -= .7f;
    }
}

void Cube::Fire()
{
    Logger::LogWarning("PEW PEW!!");
}

void Cube::Draw()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(ShaderProgram);

    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    // Draw the triangle !
    glDrawArrays(GL_LINE_LOOP, 0, 4); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
}

void Cube::InitializeVertexArrays()
{

    glGenVertexArrays(1, &VertexArray);
    glBindVertexArray(VertexArray);

    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &VertexBuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
}

void Cube::Initialize()
{
    if (!Utility::InitializeShaders(ShaderProgram, ShaderFragment, ShaderVertex))
    {
        Logger::LogError("Failed to Initialize, may run into issues...");
    }

    InitializeVertexArrays();

    ScalePlayer(0.4f);
    AlignPlayer();
}