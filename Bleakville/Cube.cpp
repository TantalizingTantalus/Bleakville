#include "Cube.h"

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