/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#ifndef NPC_HPP
#define NPC_HPP 1
#include "stickman/StickMan.hpp"

class NPC: public StickMan
{
  const float DELAY_TIME = 0.45f;

  int hpToDefMode;
  int procentageDefOrOff;
  int procentageAttackWait;
  int procentageWalkWait;
  float distanceOffensive;
  float distanceDefensive;
  double timeToEndWork;
  int work;

  void randomPersonality();
  void randomAttackBasedOnRange();
  void chooseWork();
  void defensive();
  void playDefensive();
  void playOffensive();

  bool isRangeOffensive() const{return getDistanceBetween().x < distanceOffensive;}
  bool isRangeDefensive() const{return getDistanceBetween().x < distanceDefensive;}
  bool wait(const int & procent);

public:
  NPC();

  virtual void think();
};
#endif
