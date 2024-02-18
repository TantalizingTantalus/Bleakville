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
#include "dependencies/glm/glm.hpp"
#include "dependencies/glm/gtc/matrix_transform.hpp"
#include "dependencies/glm/gtc/type_ptr.hpp"

class Shader 
{
public:
     
    Shader();
    bool InitializeShaders( GLuint& FragmentShader, GLuint& VertexShader);
    bool IsAnyKeyPressed(GLFWwindow* window);
    void UseShader();
    bool Cleanup();
    GLuint ShaderProgram;
private:
    bool BuildAndCompileFragment(GLuint& FragmentShader, GLint success, GLchar infoLog[512]);
    bool BuildAndCompileVertex(GLuint& VertexShader);
    bool LinkShaderProgram(GLuint VertexShader, GLuint FragmentShader, GLint success, GLchar infoLog[512]);
    const GLchar* ReadShaderSource(std::string FileName);
    
};