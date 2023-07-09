#version 330 core
in vec3 Position;  
in vec2 TexCoords;
in vec3 Normal;    

out vec4 FragColor;

struct Material {
    sampler2D texture_diffuse1; 
    sampler2D texture_bump1;  
};

uniform Material material;

uniform int useDefault = 1;
uniform int useColor = 0;
uniform int useTexture = 0;
uniform int useBump = 0;

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
            color = vec3(0.2); // reset color
            //color *= texture(material.texture_diffuse1, vec2(Position.x, Position.y)).rgb; //debug
            color += texture(material.texture_diffuse1, TexCoords).rgb;   //always black or white
        }

        if(useBump == 1)
        {
            vec3 texNormal = normalize(texture(material.texture_bump1, TexCoords).rgb * 2.0 - 1.0); // normal from normal map

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