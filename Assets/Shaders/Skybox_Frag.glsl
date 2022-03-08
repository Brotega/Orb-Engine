#version 460 core
out vec4 FragColor;
  
in vec3 TexCoords;

struct MaterialProperty
{
    samplerCube Skybox;
}; uniform MaterialProperty materialProperty;

void main()
{
    FragColor = texture(materialProperty.Skybox, TexCoords);
}