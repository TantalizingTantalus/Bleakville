#include "Cube.h"

void Cube::updateVertexPositionsUp() {


    Logger::LogInformation("Size of tObject.vertices = " + std::to_string(VertCount));
    for (int i = 1; i < VertCount; i += 3)
    {
        vertices[i] += speed;
        Logger::LogInformation(std::to_string(vertices[i]));
        Position p = GetPosition();
        Logger::LogInformation("X: " + std::to_string(p.x));
        Logger::LogInformation("Y: " + std::to_string(p.y));
    }
}

void Cube::updateVertexPositionsDown() {

    Logger::LogInformation("Size of tObject.vertices = " + std::to_string(VertCount));
    for (int i = 1; i < VertCount; i += 3)
    {
        vertices[i] -= speed;
        Logger::LogInformation(std::to_string(vertices[i]));
        Position p = GetPosition();
        Logger::LogInformation("X: " + std::to_string(p.x));
        Logger::LogInformation("Y: " + std::to_string(p.y));
    }
}

void Cube::updateVertexPositionsLeft() {


    Logger::LogInformation("Size of tObject.vertices = " + std::to_string(VertCount));

    for (int i = 0; i < VertCount; i += 3)
    {
        vertices[i] -= speed;
        Logger::LogInformation(std::to_string(vertices[i]));
        Position p = GetPosition();
        Logger::LogInformation("X: " + std::to_string(p.x));
        Logger::LogInformation("Y: " + std::to_string(p.y));
    }

}

void Cube::updateVertexPositionsRight() {

    for (int i = 0; i < VertCount; i += 3)
    {
        vertices[i] += speed;
        Logger::LogInformation(std::to_string(vertices[i]));
        Position p = GetPosition();
        Logger::LogInformation("X: " + std::to_string(p.x));
        Logger::LogInformation("Y: " + std::to_string(p.y));
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