//Copyright (c) 2020 by Stan Fortoński
#version 410 core

out vec4 fragColor;
uniform float width;

float map(float value, float min1, float max1, float min2, float max2)
{
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

void main()
{
  float factor = map(gl_FragCoord.x, 1.0, width, 0.0, 1.0);
  if (gl_FragCoord.x > width/2)
    fragColor = vec4(0.01, 0.01, 0.01, (1.0 - factor)*1.5);
  else fragColor = vec4(0.01, 0.01, 0.01, factor*1.5);
}
