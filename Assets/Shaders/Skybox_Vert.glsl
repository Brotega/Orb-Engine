#version 460 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

layout (std140, binding = 0) uniform Camera
{
    mat4 View;
    mat4 Projection;
    vec3 CameraPosition; 
    float CameraNear;
    float CameraFar;
};

void main()
{
    TexCoords = aPos;
    gl_Position = Projection * mat4(mat3(View)) * vec4(aPos, 1.0);
}