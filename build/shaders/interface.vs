//Copyright (c) 2020 by Stan Fortoński
#version 410 core

layout (location = 0) in vec3 aPos;

void main()
{
  gl_Position = vec4(aPos.x * 0.55, aPos.y, 0.0, 1.0);
}
