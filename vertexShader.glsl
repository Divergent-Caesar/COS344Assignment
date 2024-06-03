#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexNormal_modelspace;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;

out vec3 fragmentColor;
out vec3 Normal_cameraspace;
out vec3 Position_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;

uniform vec3 lightPosition_worldspace;

void main() {
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1.0);
    fragmentColor = vertexColor;

    vec4 vertexPosition_cameraspace = V * M * vec4(vertexPosition_modelspace, 1.0);
    Position_cameraspace = vec3(vertexPosition_cameraspace) / vertexPosition_cameraspace.w;

    vec3 vertexNormal_cameraspace = (V * M * vec4(vertexNormal_modelspace, 0.0)).xyz;
    Normal_cameraspace = normalize(vertexNormal_cameraspace);

    vec3 lightPosition_cameraspace = (V * vec4(lightPosition_worldspace, 1.0)).xyz;
    LightDirection_cameraspace = lightPosition_cameraspace - Position_cameraspace;

    EyeDirection_cameraspace = vec3(0.0, 0.0, 0.0) - Position_cameraspace;
}
