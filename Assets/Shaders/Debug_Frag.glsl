#version 460 core
out vec4 FragColor;
  
in vec4 Color;

in vec3 CameraPosWS;
in float ZNear;
in float ZFar;

void main()
{
    FragColor = Color;
}