#version  430 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec4 color;
layout (location = 3) in float texIndex;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

out vec4 pos;
out vec2 texCoord;
out vec4 colour;
out float tex_index;

void main() {
    gl_Position = pr_matrix * vw_matrix * ml_matrix * position;
    pos = position;
    colour = color;
    tex_index = texIndex;
    texCoord = uv;
}