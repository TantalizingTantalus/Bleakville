

#include "Utils.h"




const std::string SHADER_DIR = "Shaders/";
const int GLFW_MAX_KEYS = 348;

bool Utility::BuildAndCompileFragment(GLuint& FragmentShader, GLint success, GLchar infoLog[512])
{
    const std::string ShaderName = "fragment_shader.frag";
    const GLchar* fragmentShaderSource = ReadShaderSource(ShaderName);
    Logger::LogInformation("Building and compiling fragment shader " + ShaderName);
    // Build and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check for fragment shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        Logger::LogInformation("Fragment shader compilation failed:\n" + (std::string)infoLog);
    }

    FragmentShader = fragmentShader;
    return success;
}

bool Utility::IsAnyKeyPressed(GLFWwindow* window)
{
    for (int key = GLFW_KEY_SPACE; key <= GLFW_MAX_KEYS; ++key) {
        if (glfwGetKey(window, key) == GLFW_PRESS) {
            return true;
        }
    }
    return false;
}

bool Utility::BuildAndCompileVertex(GLuint& VertexShader)
{
    const std::string ShaderName = "vertex_shader.vert";
    const GLchar* vertexShaderSource = ReadShaderSource(ShaderName);
    Logger::LogInformation("Building and compiling vertex shader " + ShaderName);
    // Build and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check for vertex shader compile errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        Logger::LogInformation("Vertex shader compilation failed:\n" + (std::string)infoLog);
    }

    VertexShader = vertexShader;
    return success;
}

bool Utility::InitializeShaders(GLuint& ShaderProgram, GLuint& FragmentShader, GLuint& VertexShader)
{
    Logger::LogInformation("Initializeing shaders...");
    GLuint Success;
    GLchar infoLog[512];

    Success = BuildAndCompileVertex(VertexShader);
    if (Success)
        Logger::LogInformation("Vertex shader built and compiled successfully...");

    Success = BuildAndCompileFragment(FragmentShader, Success, infoLog);
    if (Success)
        Logger::LogInformation("Fragment shader built and compiled successfully...");

    Success = LinkShaderProgram(ShaderProgram, VertexShader, FragmentShader, Success, infoLog);
    if (Success)
        Logger::LogInformation("Successfully linked Shader Program with Vertex and Fragment shaders...");

    if (Success)
        Logger::LogInformation("All shaders initialized correctly.");
    else
        Logger::LogError("Something failed during initialization, check console logs.");

    return Success;
}

bool Utility::LinkShaderProgram(GLuint& ShaderProgram, GLuint VertexShader, GLuint FragmentShader, GLint success, GLchar infoLog[512])
{
    Logger::LogInformation
    (
        "Linking (" + std::to_string(VertexShader) + ") vertex shader with (" + std::to_string(FragmentShader) + ") fragment shader with shader program ("
        + std::to_string(ShaderProgram) + ")."
    );

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, VertexShader);
    glAttachShader(shaderProgram, FragmentShader);
    glLinkProgram(shaderProgram);

    // Check for shader program link errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        Logger::LogInformation("Shader program linking failed:\n" + (std::string)infoLog);
    }

    Logger::LogInformation("Shader linking completed successfully!");

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);

    ShaderProgram = shaderProgram;
    return success;
}


const GLchar* Utility::ReadShaderSource(std::string FileName)
{
    const std::string FilePath = SHADER_DIR + FileName;

    std::ifstream file(FilePath);
    if (!file.is_open()) {
        Logger::LogError("Failed to open shader: " + FileName);
        return nullptr;
    }

    Logger::LogInformation("Reading shader at: " + FilePath);

    // Read the file contents into a stringstream
    std::stringstream buffer;
    buffer << file.rdbuf();

    // Get the string from the stringstream
    std::string shaderSourceStr = buffer.str();

    // Allocate memory for the shader source dynamically
    const GLchar* shaderSource = new GLchar[shaderSourceStr.size() + 1];

    // Copy the shader source string to the allocated memory
    strcpy_s(const_cast<char*>(shaderSource), shaderSourceStr.size() + 1, shaderSourceStr.c_str());

    // Close the file
    file.close();

    return shaderSource;
}