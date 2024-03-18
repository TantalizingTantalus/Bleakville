#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D transform;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
    
}