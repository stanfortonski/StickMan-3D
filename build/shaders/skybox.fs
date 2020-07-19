//Copyright (c) 2020 by Stan Fortoński
#version 410 core

out vec4 fragColor;
in vec3 texCoords;

const int CELL_SHADING_LEVELS = 9;

uniform samplerCube skybox;

void main()
{
  vec3 color = texture(skybox, texCoords).rgb;
  float avgColorFactor = (color.r + color.g + color.b)/3.0;
  avgColorFactor = floor(avgColorFactor * CELL_SHADING_LEVELS)/CELL_SHADING_LEVELS;
  color = avgColorFactor * vec3(1.0, 1.0, 1.0);
  color *= vec3(0.11, 0.6, 1.0);

  fragColor = vec4(color, 1.0);
}
