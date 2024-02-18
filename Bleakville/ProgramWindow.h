#pragma once
#include "Cube.h"


class PWindow
{
public:
    GLsizei WINDOW_HEIGHT;
    GLsizei WINDOW_WIDTH;
    GLFWwindow* WindowContext;

    PWindow();


    bool InitializeWindow();
    void SetWindowSize(int h, int w);
    static GLuint GetShader();
};









