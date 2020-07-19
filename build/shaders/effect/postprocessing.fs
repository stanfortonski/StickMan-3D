//Copyright (c) 2020 by Stan Fortoński
#version 410 core

out vec4 fragColor;
in vec2 texCoords;

uniform sampler2D screenTexture0;
uniform float slowMotion;

void main()
{
  fragColor = vec4(texture(screenTexture0, texCoords).xyz, slowMotion);
}
