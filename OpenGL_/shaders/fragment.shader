#version 330 core

out vec4 FragColor;

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D theTexture;

void main() {
	FragColor = texture(theTexture, texCoord);
}