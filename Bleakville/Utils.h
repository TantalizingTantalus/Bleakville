#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string.h>
#include <sstream>
#include "Vec2D.h"
#include "Logging.h"
#include "Transform.h"
#include "dependencies/include/stb_load/stb_image.h"

class Utility 
{
public:
     
    Utility();
    static bool InitializeShaders(GLuint& ShaderProgram, GLuint& FragmentShader, GLuint& VertexShader);
    static bool IsAnyKeyPressed(GLFWwindow* window);
    static void UseShader(GLuint& ShaderProgram);
    static bool Cleanup(GLuint& ShaderProgram);
private:
    static bool BuildAndCompileFragment(GLuint& FragmentShader, GLint success, GLchar infoLog[512]);
    static bool BuildAndCompileVertex(GLuint& VertexShader);
    static bool LinkShaderProgram(GLuint& ShaderProgram, GLuint VertexShader, GLuint FragmentShader, GLint success, GLchar infoLog[512]);
    static const GLchar* ReadShaderSource(std::string FileName);
};