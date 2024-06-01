#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexNormal_modelspace;

out vec3 fragmentColor;
out vec3 fragmentNormal;
out vec3 fragmentPosition;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;

void main() {
    // Output position of the vertex
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1.0);

    // Fragment color
    fragmentColor = vertexColor;

    // Transform the normal's orientation
    fragmentNormal = mat3(transpose(inverse(M))) * vertexNormal_modelspace;

    // Transform the position
    fragmentPosition = vec3(M * vec4(vertexPosition_modelspace, 1.0));
}
