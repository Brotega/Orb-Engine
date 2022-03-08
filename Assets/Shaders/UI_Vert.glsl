#version 460 core
layout (location = 0) in vec3 aPos;
  
out vec4 Color;

uniform vec4 color;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    Color = color;
}