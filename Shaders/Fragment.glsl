#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

// Default uniform values
uniform vec3 lightPos = vec3(3.0, 5.0, 2.0); // Default light position
uniform vec3 viewPos = vec3(0.0, 0.0, 3.0);  // Default camera position
uniform vec3 lightColor = vec3(1.0, 1.0, 1.0); // White light
uniform vec3 objectColor = vec3(0.7, 0.2, 0.3); // Default object color

void main() {
    // Normalize normal
    vec3 norm = normalize(Normal);

    // Compute light direction
    vec3 lightDir = normalize(lightPos - FragPos);

    // Diffuse lighting
    float diff = max(dot(norm, lightDir), 0.0);

    // View direction
    vec3 viewDir = normalize(viewPos - FragPos);

    // Specular lighting (Phong)
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    // Combine lighting
    vec3 ambient = 0.2 * lightColor;
    vec3 diffuse = diff * lightColor;
    vec3 specular = spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
