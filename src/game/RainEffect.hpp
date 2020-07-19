/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#ifndef RAIN_EFFECT_HPP
#define RAIN_EFFECT_HPP 1
#include "../../src/engine/effect/ParticlesGenerator.hpp"
#include "../../src/engine/renderable/shape/Cube.hpp"
#include "../../src/engine/Config.hpp"

class RainParticle: public Engine::StandardParticle
{
public:
  float speed = 0.1f;
};

class RainEffect: public Engine::ParticlesGenerator<RainParticle, Engine::Cube>
{
  glm::vec3 offset;
  float speed = 0.1f;

protected:
  virtual void respawnParticle(RainParticle & particle);
  virtual bool updateParticle(RainParticle & particle, const float & dt);

public:
  RainEffect(Engine::InterfaceCamera * cam, Engine::Program & program):
  Engine::ParticlesGenerator<RainParticle, Engine::Cube>(cam, program), offset(glm::vec3(4.0f, 20.0f, 4.0f))
  {
    const glm::vec3 vScale = glm::vec3(0.001f, 0.004f, 0.001f);
    scale(vScale);
    offset /= vScale;
  }
};
#endif
