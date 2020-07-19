//Copyright (c) 2020 by Stan Fortoński
#version 410 core

out vec4 color;

in VS_OUT
{
  vec2 texCoords;
  vec4 particleColor;
} fs_in;

void main()
{
  color = fs_in.particleColor;
}
