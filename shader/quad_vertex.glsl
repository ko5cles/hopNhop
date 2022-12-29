#version 330 core

layout (location=0) in vec3 position;
out vec2 frag_pos;

void main() {
    gl_Position=vec4(position,1);
    frag_pos=(position.xy+vec2(1,1))/2.f;
}
