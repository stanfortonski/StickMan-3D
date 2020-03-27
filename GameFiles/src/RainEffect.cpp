/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#include "RainEffect.hpp"

void RainEffect::respawnParticle(RainParticle & p)
{
  if (p.position.y <= 0)
  {
    int signX = (rand()%1) == 1 ? : -1;
    int signY = (rand()%1) == 1 ? : -1;
    p.position = glm::vec3((rand()%((int)offset.x)) * signX, (rand()%((int)offset.y)) + offset.y, (rand()%((int)offset.z)) * signY);
    p.color = glm::vec4(0.03f, 0.4f, 1.0f, 0.95f);
    p.speed = speed * (rand()%((int)(offset.y))) * 0.2;
  }
}

bool RainEffect::updateParticle(RainParticle & p, const float & dt)
{
  if (p.position.y > 0)
  {
    p.speed += speed;
    p.position += Engine::Config::get().getGravity() * dt * p.speed;
    return true;
  }
  return false;
}
