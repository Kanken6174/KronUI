#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 Position;  // output to the fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    Position = aPos;  // pass the position to the fragment shader
}