//Copyright (c) 2020 by Stan Fortoński
#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in ivec4 boneIds;
layout (location = 4) in vec4 weights;

out VS_OUT
{
  vec3 fragPos;
  vec3 normal;
  vec2 texCoords;
} vs_out;

const int MAX_BONES = 100;

uniform mat4 viewProject;
uniform mat4 model;
uniform mat4 bones[MAX_BONES];
uniform vec4 clipPlane;

void main()
{
  mat4 boneTransform = bones[boneIds[0]] * weights[0];
  	boneTransform += bones[boneIds[1]] * weights[1];
  	boneTransform += bones[boneIds[2]] * weights[2];
  	boneTransform += bones[boneIds[3]] * weights[3];

  vec4 bonePosition = boneTransform * vec4(aPos, 1.0);
  vs_out.fragPos = vec3(model * bonePosition);
  vs_out.texCoords = aTexCoords;
  vs_out.normal = normalize(vec3(model * boneTransform * vec4(aNormal, 0.0)));

  gl_ClipDistance[0] = dot(vec4(vs_out.fragPos, 1.0), clipPlane);
  gl_Position = viewProject * model * bonePosition;
}
