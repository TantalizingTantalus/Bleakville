#include <iostream>
#include "TriangleObject.h"
#include "Utils.h"

// Vertex buffer object (VBO) ID
unsigned int VBO;

const GLsizei WINDOW_HEIGHT = 800;
const GLsizei WINDOW_WIDTH = 1000;

Triangle tObject;

// Vertex shader source
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    void main() {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)";

// Fragment shader source
const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(.41f, .75f, .75f, 1.0f);
    }
)";

// Shader forward declares
bool BuildAndCompileVertex(GLuint& VertexShader);
bool BuildAndCompileFragment(GLuint& FragmentShader, GLint success, GLchar infoLog[512]);
bool LinkShaderProgram(GLuint& ShaderProgram, GLuint VertexShader, GLuint FragmentShader, GLint success, GLchar infoLog[512]);
bool InitializeShaders(GLuint& ShaderProgram, GLuint& FragmentShader, GLuint& VertexShader);

void scaleTriangle(float factor) {
    
    for (int i = 0; i < tObject.VertCount; ++i) {
        tObject.vertices[i] *= factor;
    }
}


void AlignTriangle()
{
    
    for (int i = 1; i < tObject.VertCount; i += 3)
    {
        tObject.vertices[i] -= .7f;
        
    }
}

void updateVertexPositionsUp() {
    
    
    Logger::LogInformation("Size of tObject.vertices = " + std::to_string(tObject.VertCount));
    for (int i = 1; i < tObject.VertCount; i+= 3)
    {
        tObject.vertices[i] += tObject.speed;
        Logger::LogInformation(std::to_string(tObject.vertices[i]));
        Position p = tObject.GetPosition();
        Logger::LogInformation("X: " + std::to_string(p.x));
        Logger::LogInformation("Y: " + std::to_string(p.y));
    }
}

void updateVertexPositionsDown() {
    
    Logger::LogInformation("Size of tObject.vertices = " + std::to_string(tObject.VertCount));
    for (int i = 1; i < tObject.VertCount; i+=3)
    {
        tObject.vertices[i] -= tObject.speed;
        Logger::LogInformation(std::to_string(tObject.vertices[i]));
        Position p = tObject.GetPosition();
        Logger::LogInformation("X: " + std::to_string(p.x));
        Logger::LogInformation("Y: " + std::to_string(p.y));
    }
}

void updateVertexPositionsLeft() {

    
    Logger::LogInformation("Size of tObject.vertices = " + std::to_string(tObject.VertCount));
    
    for (int i = 0; i < tObject.VertCount; i += 3)
    {
            tObject.vertices[i] -= tObject.speed;
            Logger::LogInformation(std::to_string(tObject.vertices[i]));
            Position p = tObject.GetPosition();
            Logger::LogInformation("X: " + std::to_string(p.x));
            Logger::LogInformation("Y: " + std::to_string(p.y));
    }
    
}

void updateVertexPositionsRight() {
    
    for (int i = 0; i < tObject.VertCount; i += 3)
    {
        tObject.vertices[i] += tObject.speed;
        Logger::LogInformation(std::to_string(tObject.vertices[i]));
        Position p = tObject.GetPosition();
        Logger::LogInformation("X: " + std::to_string(p.x));
        Logger::LogInformation("Y: " + std::to_string(p.y));
    }
    
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        Logger::LogInformation("Failed to initialize GLFW");
        return -1;
    }


    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Bleakville", NULL, NULL);
    if (!window) {
        Logger::LogInformation("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Logger::LogInformation("Failed to initialize GLAD");
        glfwTerminate();
        return -1;
    }

    GLuint VertexShader;
    GLuint FragmentShader;
    GLuint ShaderProgram;

    if (!InitializeShaders(ShaderProgram, FragmentShader, VertexShader))
    {
        Logger::LogError("Failed to Initialize :(");
        return 0;
    }

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s)
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tObject.vertices), tObject.vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
    glBindVertexArray(0); // Unbind VAO

    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);
    scaleTriangle(0.4f);
    AlignTriangle();

    // Set up the viewport
    glViewport(NULL, NULL, WINDOW_WIDTH, WINDOW_HEIGHT);
    bool PausePressed = false;
    bool added = false;
    bool subtracted = false;
    
    Logger::LogInformation("Starting loop...");

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            break;
        }

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !PausePressed)
        {
            Logger::LogWarning("Paused!");
            PausePressed = true;
        }
        else {
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
            {
                PausePressed = false;
            }
        }

        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            Logger::LogInformation("W is being presssed!");
            updateVertexPositionsUp();
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            Logger::LogInformation("S is being presssed!");
            updateVertexPositionsDown();
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            Logger::LogInformation("A is being presssed!");
            updateVertexPositionsLeft();
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            Logger::LogInformation("D is being presssed!");
            updateVertexPositionsRight();
        }

        if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS && !added)
        {
            tObject.speed += 0.01f;
            added = true;
            Logger::LogInformation("Value of tObject.speed (" + std::to_string(tObject.speed) + ")");
        }
        else {
            if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_RELEASE)
            {
                added = false;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS && !subtracted)
        {
            if (tObject.speed >= 0)
            {
                tObject.speed -= 0.01f;
                subtracted = true;
                Logger::LogInformation("Value of tObject.speed (" + std::to_string(tObject.speed) + ")");
            }
            else
            {
                tObject.speed = 0.001f;
                subtracted = true;
            }
            
        }
        else {
            if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_RELEASE)
            {
                subtracted = false;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        {
            Logger::LogInformation("R is being presssed!");
        }

        // Bind the VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // Update the vertex data
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(tObject.vertices), tObject.vertices);

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use shader program
        glUseProgram(ShaderProgram);
        // Draw triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_LOOP, 0,  4);

        
        glBindVertexArray(0);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(ShaderProgram);

    // Terminate GLFW
    glfwTerminate();

    Logger::LogWarning("Program completed successfully!");
    return 0;
}

// Build and compile vertex first
bool BuildAndCompileVertex(GLuint& VertexShader)
{
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

// Build and compile Fragments second
bool BuildAndCompileFragment(GLuint& FragmentShader, GLint success, GLchar infoLog[512])
{
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

bool LinkShaderProgram(GLuint& ShaderProgram, GLuint VertexShader, GLuint FragmentShader, GLint success, GLchar infoLog[512])
{
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

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);

    ShaderProgram = shaderProgram;
    return success;
}

bool InitializeShaders(GLuint& ShaderProgram, GLuint& FragmentShader, GLuint& VertexShader)
{
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
        Logger::LogWarning("All shaders initialized correctly.");
    else
        Logger::LogError("Something failed during initialization, check console logs.");

    return Success;
}