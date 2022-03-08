#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aTangent;
layout (location = 3) in vec3 aBinormal;
layout (location = 4) in vec2 aUV;

out vec3 WorldPos;
out vec3 Normal;
out vec3 Tangent;
out vec3 Binormal;
out vec2 UV;
out vec3 UVW;

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

    WorldPos = vec3(model * vec4(aPos, 1.0f));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    Tangent = mat3(transpose(inverse(model))) * aTangent;
    Binormal = mat3(transpose(inverse(model))) * aBinormal;
    UV = aUV;
    UVW = aPos;

    gl_Position = Projection * View * vec4(WorldPos, 1.0f);
}