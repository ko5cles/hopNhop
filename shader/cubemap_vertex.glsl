#version 330 core

layout (location = 0) in vec3 position;
out vec3 tcoord;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main()
{
    tcoord = vec3(position.x,position.z,position.y);
    vec4 pos = projMatrix * viewMatrix * modelMatrix* vec4(position, 1.0);
    gl_Position = pos.xyww;
}