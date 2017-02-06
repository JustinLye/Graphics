#version 330 core
in vec2 TexCoord;
out vec4 color;
uniform sampler2D texture_01;
void main() {
    color = texture(texture_01, TexCoord);
}