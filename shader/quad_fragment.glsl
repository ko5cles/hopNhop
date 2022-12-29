#version 330 core
in vec2 frag_pos;
out vec4 fragment_color;
uniform sampler2D quad_texture;
void main() {
    float depthValue = texture(quad_texture, frag_pos).r;
    fragment_color=vec4(vec3(depthValue),1);
}
