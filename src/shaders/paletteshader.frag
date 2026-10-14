#version 330 core
out vec4 FragColor;
in vec3 vertexColor;
in vec3 vertexPosition;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float weight;

void main()
{
   FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(TexCoord.x * -1.0f, TexCoord.y)), weight);
};
