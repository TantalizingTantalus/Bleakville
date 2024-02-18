#include "ProgramWindow.h"

PWindow::PWindow()
{
    WINDOW_HEIGHT = 800;
    WINDOW_WIDTH = 1200;
    WindowContext = nullptr;
}

GLuint PWindow::GetShader()
{
    return 0;
}

bool PWindow::InitializeWindow()
{
    // Initialize GLFW
    if (!glfwInit()) {
        Logger::LogError("Failed to initialize GLFW");
        return false;
    }

    // Create a windowed mode window and its OpenGL context
    WindowContext = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Bleakville", NULL, NULL);
    if (!WindowContext) {
        Logger::LogError("Failed to create GLFW window");
        glfwTerminate();
        return false;
    }

    // Make the window's context current
    glfwMakeContextCurrent(WindowContext);
    gladLoadGL();

    // Set up the viewport
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Logger::LogInformation("Failed to initialize GLAD");
        glfwTerminate();
        return -1;
    }

    glfwSetWindowAttrib(WindowContext, GLFW_RESIZABLE, GLFW_FALSE);
}

void PWindow::SetWindowSize(int h, int w)
{
    WINDOW_HEIGHT = h;
    WINDOW_WIDTH = w;
    glfwSetWindowSize(WindowContext, w, h);
    // Set up the viewport
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}
