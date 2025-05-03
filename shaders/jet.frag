#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec3 Color;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    // Sun light properties - bright and slightly yellowish
    vec3 sunColor = vec3(1.0, 0.95, 0.8); 
    
    // Ambient
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * Color;

    // Diffuse - using directional light for sun
    vec3 norm = normalize(Normal);
    // Use a fixed direction for the sun, coming from above
    vec3 lightDir = normalize(vec3(0.5, -1.0, 0.3)); 
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * sunColor * Color;

    // Specular 
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * sunColor;

    // Final color
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
