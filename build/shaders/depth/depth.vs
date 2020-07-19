//Copyright (c) 2020 by Stan Fortoński
#version 410 core

layout (location = 0) in vec3 aPos;

uniform mat4 model;

void main()
{
  gl_Position = model * vec4(aPos, 1.0);
}
