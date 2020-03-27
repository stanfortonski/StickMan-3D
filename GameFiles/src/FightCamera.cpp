/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/
#include "FightCamera.hpp"

void FightCamera::setFightView(StickMan & stickman)
{
  setFov(46);
  setPosition(glm::vec3(stickman.getPosition().x + stickman.getDistanceBetween().x/2, 1.15f, 3.4f));
  setPitch(-7.5);
  setYaw(-90);
  updateVectors();
}

void FightCamera::setFaceView1()
{
  setFov(46);
  setPosition(glm::vec3(0.0f, 1.1f, 0.0f));
  setPitch(-10);
  setYaw(180);
  updateVectors();
}

void FightCamera::setFaceView2()
{
  setFov(46);
  setPosition(glm::vec3(0.0f, 1.1f, 0.0f));
  setPitch(-10);
  setYaw(0.0);
  updateVectors();
}

void FightCamera::setMapView()
{
  static const float radius = 2.0f;
  float camX = sin(glfwGetTime() * 0.125) * radius,
        camZ = cos(glfwGetTime() * 0.125) * radius;
  setPosition(glm::vec3(camX, 18.0f, 18.0f - camZ));
  setPitch(-55);
  setYaw(-90);
  setFov(50);
  updateVectors();
}
