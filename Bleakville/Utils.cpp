#include <glad/glad.h>
#include <string.h>
#include "Utils.h"

//bool Utility::BuildAndCompileFragment(GLuint& FragmentShader, GLint success, GLchar infoLog[512])
//{
//    // Build and compile the fragment shader
//    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShader);
//
//    // Check for fragment shader compile errors
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//    if (!success) {
//        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//        Logger::LogInformation("Fragment shader compilation failed:\n" + (std::string)infoLog);
//    }
//
//    FragmentShader = fragmentShader;
//    return success;
//}