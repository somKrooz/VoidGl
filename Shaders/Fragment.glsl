#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 lightPos;        // Light position
uniform vec3 viewPos;         // Camera position
uniform vec3 lightColor;      // Light color (adjusted to be cooler)
uniform vec3 objectColor;     // Object base color

void main() {
    // Normalize normal vector
    vec3 norm = normalize(Normal);

    // Compute light direction
    vec3 lightDir = normalize(lightPos - FragPos);

    // Diffuse lighting (balanced intensity)
    float diff = max(dot(norm, lightDir), 0.0) * 0.8; // Reduced brightness

    // Blinn-Phong Specular lighting (cooler highlights)
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0) * 0.5; // Lower intensity

    // Soft Rim Lighting (cool blue rim glow)
    float rim = 1.0 - max(dot(norm, viewDir), 0.0);
    rim = pow(rim, 4.0) * 0.3; // Subtle rim effect
    vec3 rimLight = rim * vec3(0.4, 0.5, 1.0); // Cool blue rim glow

    // Soft Ambient Light (cool and balanced)
    vec3 ambient = vec3(0.1, 0.15, 0.2);  // Soft blue ambient light

    // Final Lighting Calculation
    vec3 diffuse = diff * lightColor * 0.8; // Keep colors natural
    vec3 specular = spec * vec3(0.6, 0.7, 1.0); // Blue-tinted highlights

    vec3 finalColor = (ambient + diffuse + specular + rimLight) * objectColor;

    // Gamma correction for realistic color balance
    finalColor = pow(finalColor, vec3(1.0 / 2.2));

    FragColor = vec4(finalColor, 1.0);
}
