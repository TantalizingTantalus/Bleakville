// Fragment shader source  "fragment_shader.frag"

#version 330 core

out vec4 FragColor;
in vec4 VertColor;

void main()
{
    FragColor = VertColor;
}