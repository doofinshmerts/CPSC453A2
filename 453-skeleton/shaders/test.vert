#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in int textureID;
layout (location = 3) in mat4 transform;

out vec2 TexCoord;
flat out int texID;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
    texID = textureID;
}