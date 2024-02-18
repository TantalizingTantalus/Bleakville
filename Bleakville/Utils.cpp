

#include "Utils.h"


const std::string SHADER_DIR = "Shaders/";
const int GLFW_MAX_KEYS = 348;

Shader::Shader()
{
    Logger::LogInformation("Utility object successfully built...ready to use");
}

bool Shader::BuildAndCompileFragment(GLuint& FragmentShader, GLint success, GLchar infoLog[512])
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

bool Shader::IsAnyKeyPressed(GLFWwindow* window)
{
    for (int key = GLFW_KEY_SPACE; key <= GLFW_MAX_KEYS; ++key) {
        if (glfwGetKey(window, key) == GLFW_PRESS) {
            return true;
        }
    }
    return false;
}

bool Shader::BuildAndCompileVertex(GLuint& VertexShader)
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

bool Shader::InitializeShaders( GLuint& FragmentShader, GLuint& VertexShader)
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

    Success = LinkShaderProgram(VertexShader, FragmentShader, Success, infoLog);
    if (Success)
        Logger::LogInformation("Successfully linked Shader Program with Vertex and Fragment shaders...");

    if (Success)
        Logger::LogInformation("All shaders initialized correctly.");
    else
        Logger::LogError("Something failed during initialization, check console logs.");


    return Success;
}

bool Shader::LinkShaderProgram(GLuint VertexShader, GLuint FragmentShader, GLint success, GLchar infoLog[512])
{
    Logger::LogInformation
    (
        "Linking (" + std::to_string(VertexShader) + ") vertex shader with (" + std::to_string(FragmentShader) + ") fragment shader with shader program ("
        + std::to_string(ShaderProgram) + ")."
    );

    // Link the vertex and fragment shader into a shader program
    ShaderProgram = glCreateProgram();
    glAttachShader(ShaderProgram, VertexShader);
    glAttachShader(ShaderProgram, FragmentShader);
    glLinkProgram(ShaderProgram);

    // Check for shader program link errors
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ShaderProgram, 512, NULL, infoLog);
        Logger::LogInformation("Shader program linking failed:\n" + (std::string)infoLog);
    }

    Logger::LogInformation("Shader linking completed successfully!");

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);

    
    return success;
}

void Shader::UseShader()
{
    glUseProgram(ShaderProgram);
    return;
}

bool Shader::Cleanup()
{
    try {
        if (!ShaderProgram)
            throw std::runtime_error("Invalid shader program.");

        // Cleanup code here...
        glDeleteProgram(ShaderProgram);

        //..........................
        Logger::LogInformation("Successfully cleaned up after myself :)");
        return true;
    }
    catch (const std::exception& e)
    {
        Logger::LogError("Ran into issues during cleanup:\n" + std::string(e.what()));
        return false;
    }

}


const GLchar* Shader::ReadShaderSource(std::string FileName)
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