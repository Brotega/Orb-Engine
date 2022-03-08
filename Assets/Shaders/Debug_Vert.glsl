#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
  
out vec4 Color;

out vec3 CameraPosWS;
out float ZNear;
out float ZFar;

layout (std140, binding = 0) uniform Camera
{
    mat4 View;
    mat4 Projection;
    vec3 CameraPosition; 
    float CameraNear;
    float CameraFar;
};

uniform mat4 model;

void main()
{
    CameraPosWS = CameraPosition;
    ZNear = CameraNear;
    ZFar = CameraFar;

    gl_Position = Projection * View * model * vec4(aPos, 1.0);
    Color = aColor;
}