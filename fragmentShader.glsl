#version 330 core

in vec3 fragmentColor;
in vec3 Normal_cameraspace;
in vec3 Position_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

out vec3 color;

uniform vec3 lightColor;
uniform vec3 ambientLight;

void main() {
    vec3 MaterialDiffuseColor = fragmentColor;
    vec3 MaterialAmbientColor = ambientLight * MaterialDiffuseColor;
    vec3 MaterialSpecularColor = vec3(0.3, 0.3, 0.3);

    float distance = length(LightDirection_cameraspace);
    vec3 n = normalize(Normal_cameraspace);
    vec3 l = normalize(LightDirection_cameraspace);

    float cosTheta = clamp(dot(n, l), 0, 1);
    
    vec3 E = normalize(EyeDirection_cameraspace);
    vec3 R = reflect(-l, n);
    float cosAlpha = clamp(dot(E, R), 0, 1);

    color = 
        MaterialAmbientColor +
        lightColor * MaterialDiffuseColor * cosTheta +
        lightColor * MaterialSpecularColor * pow(cosAlpha, 5);
}
