//Copyright (c) 2020 by Stan Fortoński
#version 410 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;
layout(location = 2) in vec3 aOffset;
layout(location = 3) in vec4 aColor;

out VS_OUT
{
  vec2 texCoords;
  vec4 particleColor;
} vs_out;

uniform mat4 viewProject;
uniform mat4 model;

void main()
{
  vs_out.texCoords = aTexCoords;
  vs_out.particleColor = aColor;
  gl_Position = viewProject * model * vec4(aPos + aOffset, 1.0);
}
