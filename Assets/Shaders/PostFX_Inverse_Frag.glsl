#version 460 core
out vec4 FragColor;
  
in vec2 UV;

struct MaterialProperty
{
    sampler2D Texture;
}; uniform MaterialProperty materialProperty;

void main()
{
    FragColor = vec4(1 - vec3(texture(materialProperty.Texture, UV)), 1.0f);
}