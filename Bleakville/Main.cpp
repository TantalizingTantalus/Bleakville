
#include "ProgramWindow.h"

PWindow Window;
Cube ControllerCube;
Cube Enemy;

int main() {
    
    if (!Window.InitializeWindow())
    {
        Logger::LogError("Failed to intialize window...");
        return 0;
    }
    
    ControllerCube.Initialize();
    Enemy.TexturePath = "/Artwork/wall.jpg";
    Enemy.Initialize();

    bool PausePressed = false, added = false, subtracted = false, psubtracted = false, padded = false;
    
    Logger::LogInformation("Starting loop...");

    // Render loop
    while (!glfwWindowShouldClose(Window.WindowContext)) {

        ControllerCube.CubeShader.UseShader();
        Enemy.CubeShader.UseShader();

        if (glfwGetKey(Window.WindowContext, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            Logger::LogInformation("Exiting!");
            break;
        }

        if (glfwGetKey(Window.WindowContext, GLFW_KEY_SPACE) == GLFW_PRESS && !PausePressed)
        {
            ControllerCube.Fire();
            PausePressed = true;
        }
        else {
            if (glfwGetKey(Window.WindowContext, GLFW_KEY_SPACE) == GLFW_RELEASE)
            {
                PausePressed = false;
            }
        }

        if(glfwGetKey(Window.WindowContext, GLFW_KEY_W) == GLFW_PRESS)
        {
            ControllerCube.updateVertexPositionsUp();
        }

        if (glfwGetKey(Window.WindowContext, GLFW_KEY_S) == GLFW_PRESS)
        {
            ControllerCube.updateVertexPositionsDown();
        }

        if (glfwGetKey(Window.WindowContext, GLFW_KEY_A) == GLFW_PRESS)
        {
            ControllerCube.updateVertexPositionsLeft();
        }

        if (glfwGetKey(Window.WindowContext, GLFW_KEY_D) == GLFW_PRESS)
        {
            ControllerCube.updateVertexPositionsRight();
        }

        if (glfwGetKey(Window.WindowContext, GLFW_KEY_KP_ADD) == GLFW_PRESS && !added)
        {
            ControllerCube.speed += 0.01f;
            added = true;
            Logger::LogInformation("Value of tObject.speed (" + std::to_string(ControllerCube.speed * 100) + ")");
            
        }
        else {
            if (glfwGetKey(Window.WindowContext, GLFW_KEY_KP_ADD) == GLFW_RELEASE)
            {
                added = false;
            }
        }

        if (glfwGetKey(Window.WindowContext, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS && !subtracted)
        {
            ControllerCube.speed -= 0.01f;
            subtracted = true;
            Logger::LogInformation("Value of tObject.speed (" + std::to_string(ControllerCube.speed * 100) + ")");

        }
        else {
            if (glfwGetKey(Window.WindowContext, GLFW_KEY_KP_SUBTRACT) == GLFW_RELEASE)
            {
                subtracted = false;
            }
        }

        if (glfwGetKey(Window.WindowContext, GLFW_KEY_PAGE_UP) == GLFW_PRESS && !padded)
        {
            Window.SetWindowSize(Window.WINDOW_HEIGHT + 100, Window.WINDOW_WIDTH + 100);
            padded = true;
            Logger::LogInformation("Value of tObject.speed (" + std::to_string(ControllerCube.speed * 100) + ")");

        }
        else {
            if (glfwGetKey(Window.WindowContext, GLFW_KEY_PAGE_UP) == GLFW_RELEASE)
            {
                padded = false;
            }
        }

        if (glfwGetKey(Window.WindowContext, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS && !psubtracted)
        {
                Window.SetWindowSize(Window.WINDOW_HEIGHT - 100, Window.WINDOW_WIDTH - 100);
                psubtracted = true;
                Logger::LogInformation("Value of WINDOW_HEIGHT: " + std::to_string(Window.WINDOW_HEIGHT) + "\nValue of WINDOW_WIDTH: " + std::to_string(Window.WINDOW_WIDTH));
            
        }
        else {
            if (glfwGetKey(Window.WindowContext, GLFW_KEY_PAGE_DOWN) == GLFW_RELEASE)
            {
                psubtracted = false;
            }
        }

        if (glfwGetKey(Window.WindowContext, GLFW_KEY_R) == GLFW_PRESS)
        {
            Logger::LogInformation("R is being presssed!");
        }

        Enemy.Draw();
        ControllerCube.Draw();
        

        // Swap buffers and poll events
        glfwSwapBuffers(Window.WindowContext);
        glfwPollEvents();
    }
    if (!ControllerCube.CubeShader.Cleanup())
    {
        Logger::LogWarning("Exited without properly cleaning up...");
    }

    // Terminate GLFW
    glfwTerminate();

    Logger::LogWarning("Program completed successfully!");
    return 0;
}

