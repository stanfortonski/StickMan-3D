/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#ifndef FIGHT_CAMERA_HPP
#define FIGHT_CAMERA_HPP 1
#include "../../src/engine/camera/PerspectiveCamera.hpp"
#include "stickman/StickMan.hpp"

class FightCamera: public Engine::PerspectiveCamera
{
public:
  using Engine::PerspectiveCamera::PerspectiveCamera;

  void setFightView(StickMan & stickman);
  void setFaceView1();
  void setFaceView2();
  void setMapView();
};
#endif
