#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
    FragPos = vec3(model * vec4(pos, 1.0f));
    Normal = mat3(transpose(inverse(model))) * normal;
    TexCoord = texCoord;

    gl_Position = projection * view * model * vec4(pos, 1.0f);
}
