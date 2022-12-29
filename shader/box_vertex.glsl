#version 330 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform mat4 lightSpaceMatrix;

layout (location=0) in vec3 position;
layout (location=1) in vec3 normal;
layout (location=2) in vec2 texcoord;


out vec3 n;
out vec3 pos;
out vec2 tcoord;
out vec4 pos_lightspace;

void main()
{
    pos = vec3(modelMatrix * vec4(position, 1.0));
    gl_Position = projMatrix * viewMatrix *vec4(pos, 1.0);
    pos_lightspace=lightSpaceMatrix*vec4(pos,1.0);
    //gl_Position=pos_lightspace;
    n = transpose(inverse(mat3(modelMatrix))) * normal;
    tcoord=texcoord;
}
