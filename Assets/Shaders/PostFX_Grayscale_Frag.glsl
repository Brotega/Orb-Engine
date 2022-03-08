#version 460 core
out vec4 FragColor;
  
in vec2 UV;

struct MaterialProperty
{
    sampler2D Texture;
}; uniform MaterialProperty materialProperty;

void main()
{
    vec4 color = texture(materialProperty.Texture, UV);
    float average = (0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b) / 3.0f;
    FragColor = vec4(vec3(average), 1.0f);
}