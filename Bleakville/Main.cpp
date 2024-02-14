
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

    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);
    ControllerCube.Initialize();
    
    bool PausePressed = false;
    bool added = false;
    bool subtracted = false;
    
    Logger::LogInformation("Starting loop...");

    // Render loop
    while (!glfwWindowShouldClose(window)) {

        

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            Logger::LogInformation("Exiting!");
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
            Logger::LogInformation("Value of tObject.speed (" + std::to_string(ControllerCube.speed * 1000) + ")");
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
                Logger::LogInformation("Value of tObject.speed (" + std::to_string(ControllerCube.speed * 1000) + ")");
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
        ControllerCube.Draw();

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    Logger::LogWarning("Program completed successfully!");
    return 0;
}

