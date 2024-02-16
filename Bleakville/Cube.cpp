#include "Cube.h"

Cube::Cube()
{
    Logger::LogInformation("Player cube created!");
    EBO = NULL;
    VertexArray = NULL;
    VertexBuffer = NULL;
    Texture = NULL;
    ShaderFragment = NULL;
    ShaderVertex = NULL;
    h = NULL;
    w = NULL;
    nrCh = NULL;
}

Cube::~Cube()
{
    glDeleteVertexArrays(1, &VertexArray);
    glDeleteBuffers(1, &VertexBuffer);
    glDeleteBuffers(1, &EBO);
}

void Cube::updateVertexPositionsUp() {


    for (int i = 1; i < VertCount; i += 8)
    {
        vertices[i] += speed;
    }

    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cube::updateVertexPositionsDown() {

    for (int i = 1; i < VertCount; i += 8)
    {
        vertices[i] -= speed;
    }

    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cube::updateVertexPositionsLeft() {



    for (int i = 0; i < VertCount; i += 8)
    {
        vertices[i] -= speed;
    }

    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Cube::updateVertexPositionsRight() {
    for (int i = 0; i < VertCount; i += 8)
    {
        vertices[i] += speed;
    }

    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cube::ScalePlayer(float factor)
{

    for (int i = 0; i < VertCount; ++i) {
        vertices[i] *= factor;
    }

    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cube::AlignPlayer()
{

    for (int i = 1; i < VertCount; i += 8)
    {
        vertices[i] -= .7f;
    }

    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cube::Fire()
{
    Logger::LogWarning("PEW PEW!!");
}

void Cube::Draw()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, Texture);
    glBindVertexArray(VertexArray);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Cube::InitializeGeometry()
{
    glGenVertexArrays(1, &VertexArray);
    glGenBuffers(1, &VertexBuffer);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    if (UseTextures)
    {
        try 
        {
            glGenTextures(1, &Texture);

            glBindTexture(GL_TEXTURE_2D, Texture);

            // set the texture wrapping/filtering options (on the currently bound texture object)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            unsigned char* data = stbi_load(TexturePath, &w, &h, &nrCh, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }


            stbi_image_free(data);
        }
        catch (const std::exception& e)
        {
            Logger::LogError("Ran into error loading image from path '" + std::string(TexturePath) + "' with error:\n" = std::string(e.what()));
        }
        Logger::LogInformation("Loaded from path: " + std::string(TexturePath));
    }

    
}



void Cube::Initialize(GLuint& ShaderProgram)
{
    if (!Utility::InitializeShaders(ShaderProgram, ShaderFragment, ShaderVertex))
    {
        Logger::LogError("Failed to Initialize, may run into issues...");
    }

    InitializeGeometry();

    ScalePlayer(1.0f);
    AlignPlayer();
}