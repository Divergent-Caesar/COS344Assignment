#version 330 core

in vec3 fragmentColor;
in vec3 fragmentNormal;
in vec3 fragmentPosition;

out vec3 color;

uniform vec3 lightPosition_worldspace;
uniform vec3 lightColor;
uniform vec3 ambientLight;

void main() {
    // Light properties
    vec3 lightDirection = normalize(lightPosition_worldspace - fragmentPosition);
    vec3 normal = normalize(fragmentNormal);

    // Diffuse component
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular component
    vec3 viewDirection = normalize(-fragmentPosition); // Assuming the camera is at (0,0,0)
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
    vec3 specular = spec * lightColor;

    // Ambient component
    vec3 ambient = ambientLight;

    // Combine components
    color = (ambient + diffuse + specular) * fragmentColor;
}
