
#include "Cube.h"
#include "stb_image.h"


const GLsizei WINDOW_HEIGHT = 800;
const GLsizei WINDOW_WIDTH = 1200;

Cube ControllerCube;


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
    gladLoadGL();

    // Set up the viewport
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Logger::LogInformation("Failed to initialize GLAD");
        glfwTerminate();
        return -1;
    }

    GLuint VertexShader;
    GLuint FragmentShader;
    GLuint ShaderProgram;

    if (!Utility::InitializeShaders(ShaderProgram, FragmentShader, VertexShader))
    {
        Logger::LogError("Failed to Initialize :(");
        return 0;
    }

    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);
    ControllerCube.ScalePlayer(0.4f);
    ControllerCube.AlignPlayer();

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    //draw obj
    // 
    // This will identify our vertex buffer
    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(ControllerCube.vertices), ControllerCube.vertices, GL_DYNAMIC_DRAW);


    
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
            ControllerCube.Fire();
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
            ControllerCube.updateVertexPositionsUp();
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            ControllerCube.updateVertexPositionsDown();
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            ControllerCube.updateVertexPositionsLeft();
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            ControllerCube.updateVertexPositionsRight();
        }

        if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS && !added)
        {
            ControllerCube.speed += 0.01f;
            added = true;
            Logger::LogInformation("Value of tObject.speed (" + std::to_string(ControllerCube.speed) + ")");
        }
        else {
            if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_RELEASE)
            {
                added = false;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS && !subtracted)
        {
            if (ControllerCube.speed >= 0)
            {
                ControllerCube.speed -= 0.01f;
                subtracted = true;
                Logger::LogInformation("Value of tObject.speed (" + std::to_string(ControllerCube.speed) + ")");
            }
            else
            {
                ControllerCube.speed = 0.001f;
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

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(ShaderProgram);

        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(ControllerCube.vertices), ControllerCube.vertices);
        
        // Draw the triangle !
        glDrawArrays(GL_LINE_LOOP, 0, 4); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    Logger::LogWarning("Program completed successfully!");
    return 0;
}

