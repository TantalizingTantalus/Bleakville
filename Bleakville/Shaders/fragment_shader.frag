// Fragment shader source  "fragment_shader.frag"

//#version 330 core
//out vec4 FragColor;
//  
//in vec3 ourColor;
//in vec2 TexCoord;
//
//uniform sampler2D ourTexture;
//
//void main()
//{
//    FragColor = texture(ourTexture, TexCoord);
//}

#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;\

void main()
{

    // Assign the final color to FragColor
    FragColor  = texture(ourTexture, TexCoord);
}