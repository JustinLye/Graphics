#version 330 core

in vec2 TexCoord;
uniform sampler2D ourTexture1;
out vec4 color;

void main() {
	color = texture(ourTexture1, TexCoord);
}