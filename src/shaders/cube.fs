#version 330 core
in vec3 Position;  // input from the vertex shader
in vec2 TexCoords; // texture coordinates from the vertex shader
in vec3 Normal;    // normal from the vertex shader

out vec4 FragColor;

// textures
uniform sampler2D texture_diffuse1; // color texture
uniform sampler2D texture_normal1;  // normal map

// control flags (0 = disabled, 1 = enabled)
uniform int useDefault = 1;
uniform int useColor = 0;
uniform int useTexture = 0;
uniform int useBump = 0;

// lighting
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    if(useDefault == 1)
    {
        FragColor = vec4(abs(Position), 1.0);  // use the absolute position as the color
    }
    else
    {
        vec3 color = vec3(1.0); // default white color

        if(useColor == 1)
        {
            color = abs(Position); // use the absolute position as the color
        }

        if(useTexture == 1)
        {
            color *= texture(texture_diffuse1, TexCoords).rgb;
        }

        if(useBump == 1)
        {
            vec3 texNormal = normalize(texture(texture_normal1, TexCoords).rgb * 2.0 - 1.0); // normal from normal map

            // apply lighting to the bump map here as per your preferred method, e.g. Phong, Blinn-Phong, etc.
            // for simplicity, a simple diffusive lighting is used
            vec3 lightDir = normalize(lightPos - Position);
            float diff = max(dot(texNormal, lightDir), 0.0);
            vec3 diffuse = diff * color;

            color = diffuse;
        }

        FragColor = vec4(color, 1.0);
    }
}