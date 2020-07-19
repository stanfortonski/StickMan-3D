//Copyright (c) 2020 by Stan Fortoński
#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 3) in ivec4 boneIds;
layout (location = 4) in vec4 weights;

uniform mat4 model;

const int MAX_BONES = 100;
uniform mat4 bones[MAX_BONES];

void main()
{
  mat4 boneTransform = bones[boneIds[0]] * weights[0];
  	boneTransform += bones[boneIds[1]] * weights[1];
  	boneTransform += bones[boneIds[2]] * weights[2];
  	boneTransform += bones[boneIds[3]] * weights[3];

  gl_Position = model * (boneTransform * vec4(aPos, 1.0));
}
