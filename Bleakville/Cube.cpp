#include "Cube.h"
#include "ProgramWindow.h"



Cube::Cube()
{
    Logger::LogInformation("Player cube created!");
    EBO = NULL;
    VertexArray = NULL;
    VertexBuffer = NULL;
    Texture = NULL;
    ShaderFragment = NULL;
    ShaderVertex = NULL;
}

Cube::~Cube()
{
    glDeleteVertexArrays(1, &VertexArray);
    glDeleteBuffers(1, &VertexBuffer);
    glDeleteBuffers(1, &EBO);
}

void Cube::updateVertexPositionsUp() {


    for (int i = 1; i < VertCount; i += 5)
    {
        vertices[i] += speed;
    }

    UpdateVertexBuffer();
}

void Cube::updateVertexPositionsDown() {

    for (int i = 1; i < VertCount; i += 5)
    {
        vertices[i] -= speed;
    }

    UpdateVertexBuffer();
}

void Cube::updateVertexPositionsLeft() {



    for (int i = 0; i < VertCount; i += 5)
    {
        vertices[i] -= speed;
    }

    UpdateVertexBuffer();

}

void Cube::updateVertexPositionsRight() {
    for (int i = 0; i < VertCount; i += 5)
    {
        vertices[i] += speed;
    }


    UpdateVertexBuffer();
}

void Cube::ScalePlayer(float factor, GLuint& ProgramShader)
{
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(factor, factor, factor));
    CubeShader.UseShader();
    unsigned int transformLoc = glGetUniformLocation(ProgramShader, "ModelMatrix");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(ModelMatrix));
    
    UpdateVertexBuffer();
}

void Cube::UpdateVertexBuffer()
{
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cube::AlignPlayer()
{

    for (int i = 1; i < VertCount; i += 5)
    {
        vertices[i] -= .5f;
    }

    UpdateVertexBuffer();
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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
            stbi_set_flip_vertically_on_load(true);
            int w, h, nrCh;
            unsigned char* data = stbi_load(TexturePath.c_str(), &w, &h, &nrCh, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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

void Cube::Initialize()
{
    

    if (!CubeShader.InitializeShaders( ShaderFragment, ShaderVertex))
    {
        Logger::LogError("Failed to Initialize, may run into issues...");
    }


    InitializeGeometry();
    
    ScalePlayer(0.1f, CubeShader.ShaderProgram);
    
    //AlignPlayer();

    Draw();
}