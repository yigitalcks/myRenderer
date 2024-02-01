#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aCol;
layout(location = 2) in vec2 aTex;

out vec3 vertexColor;
out vec2 texCoord;

void main() {
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	
	vertexColor = aCol;
	texCoord = aTex;
}