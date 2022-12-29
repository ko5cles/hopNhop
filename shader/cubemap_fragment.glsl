#version 330 core
out vec4 fragcolor;

in vec3 tcoord;

uniform samplerCube cubemap;

void main()
{
    fragcolor = texture(cubemap, tcoord);
}
