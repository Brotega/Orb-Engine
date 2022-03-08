#version 460 core

out vec4 FragColor;
  
in vec3 WorldPos;
in vec3 Normal;
in vec3 Tangent;
in vec3 Binormal;
in vec2 UV;

in vec3 CameraPosWS;
in float ZNear;
in float ZFar;

void main()
{
    FragColor = vec4(1.0f);
}