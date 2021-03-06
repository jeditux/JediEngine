#version 330 core

layout (location = 0) in vec2 vertexPos;
layout (location = 1) in vec2 texCoordsIn;
out vec2 texCoords;

uniform mat4 model;
uniform mat4 projection;

void main() {
    texCoords = texCoordsIn;
    gl_Position = projection * model * vec4(vertexPos, 0.0, 1.0);
}
