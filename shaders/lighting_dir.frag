#version 330 core

struct Material 
{
    vec3 ambient;
    sampler2D diffuseMap;
    vec3 specular;
    float shininess;
};

struct DirectionalLight
{
    vec3 direction; // Adjust this vector to change the direction of the light
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform DirectionalLight dirLight1;
uniform DirectionalLight dirLight2; // Second light

uniform Material material;
uniform vec3 viewPos;

out vec4 frag_color;

void main()
{ 
    vec3 finalColor = vec3(0.0);

    // Calculate lighting for the first light
    vec3 normal = normalize(Normal);
    vec3 lightDir1 = normalize(-dirLight1.direction);

    // Ambient for the first light
    vec3 ambient1 = dirLight1.ambient * material.ambient * vec3(texture(material.diffuseMap, TexCoord));

    // Diffuse for the first light
    float NdotL1 = max(dot(normal, lightDir1), 0.0);
    vec3 diffuse1 = dirLight1.diffuse * NdotL1 * vec3(texture(material.diffuseMap, TexCoord));

    // Specular for the first light
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfDir1 = normalize(lightDir1 + viewDir);
    float NDotH1 = max(dot(normal, halfDir1), 0.0);
    vec3 specular1 = dirLight1.specular * material.specular * pow(NDotH1, material.shininess);

    // Sum first light components
    finalColor += ambient1 + diffuse1 + specular1;

    // Calculate lighting for the second light
    vec3 lightDir2 = normalize(-dirLight2.direction);

    // Ambient for the second light
    vec3 ambient2 = dirLight2.ambient * material.ambient * vec3(texture(material.diffuseMap, TexCoord));

    // Diffuse for the second light
    float NdotL2 = max(dot(normal, lightDir2), 0.0);
    vec3 diffuse2 = dirLight2.diffuse * NdotL2 * vec3(texture(material.diffuseMap, TexCoord));

    // Specular for the second light
    vec3 halfDir2 = normalize(lightDir2 + viewDir);
    float NDotH2 = max(dot(normal, halfDir2), 0.0);
    vec3 specular2 = dirLight2.specular * material.specular * pow(NDotH2, material.shininess);

    // Sum second light components
    finalColor += ambient2 + diffuse2 + specular2;

    // Increase overall intensity
    finalColor *= 1.5;

    frag_color = vec4(finalColor, 1.0f);
}
