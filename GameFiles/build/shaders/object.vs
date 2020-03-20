//Copyright (c) 2020 by Stan Fortoński
#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;

out VS_OUT
{
  vec3 fragPos;
  vec3 normal;
  vec2 texCoords;
} vs_out;

uniform mat4 viewProject;
uniform mat4 model;

void main()
{
  vec4 pos = vec4(aPos, 1.0);
  vs_out.fragPos = vec3(model * pos);
  vs_out.texCoords = aTexCoords;
  vs_out.normal = normalize(transpose(inverse(mat3(model))) * aNormal);

  gl_Position = viewProject * model * pos;
}
