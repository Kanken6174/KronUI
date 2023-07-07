#version 330 core
in vec3 Position;  // input from the vertex shader

out vec4 FragColor;

void main()
{
    FragColor = vec4(abs(Position), 1.0);  // use the absolute position as the color
}