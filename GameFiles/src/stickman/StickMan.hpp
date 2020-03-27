/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#ifndef STICKMAN_HPP
#define STICKMAN_HPP 1
#include "StickManModel.hpp"

class StickMan: public StickManModel
{
  const int MAX_DISTANCE = 11;
  const int MAX_DISTANCE_BETWEEN = 4;
  const int MAX_HP = 100;
  const float HIT_BONUS_FACTOR = 0.035f;
  const float RANGE_FACT = 0.55f;
  const float DEF_BONUS_FACTOR = 0.075f;
  const float DIST_ATTENUATION = 6.4f;
  const float DAMAGE_BLOCK_PROCENT = 0.5f;
  float hp;
  unsigned attackWithoutBlockCount;
  unsigned perfectBlockCount;
  double lastAttackTime = 0;

  bool checkDistanceForward() const;
  bool checkDistanceBackward() const;

  float getMultiplierFactor(const unsigned & blockCount);
  float getHitBonus(const unsigned & attackCount);
  float getDistanceAttenuation();

protected:
  StickMan * target = nullptr;

  float calcDamageAndKick(float damage);
  float calcDamageAndPunch(float damage);
  void getHurt(float damage);

public:
  StickMan(){;}

  virtual void think(){;}
  virtual void render(Program & program);
  virtual void init();
  virtual void update();
  virtual void forwardWalk();
  virtual void backwardWalk();
  virtual bool leftPunch();
  virtual bool rightPunch();
  virtual bool leftKick();
  virtual bool rightKick();
  virtual bool kickDefense();
  virtual bool punchDefense();

  glm::vec2 getDistanceBetween() const;
  bool isAttackRange() const;
  bool isWhileAttack() const;
  bool isWhileKicking() const;
  bool isWhilePunching() const;
  bool isRange() const{return getDistanceBetween().x < RANGE_FACT;}
  bool isLeftKickRange() const{return getDistanceBetween().x < 0.95f;}
  bool isRightKickRange() const{return getDistanceBetween().x < 0.72f;}
  bool isLeftPunchRange() const{return getDistanceBetween().x < 0.87f;}
  bool isRightPunchRange() const{return getDistanceBetween().x < 1.175f;}
  bool hasNoHP() const{return hp <= 0;}
  float getHP() const{return hp;}
  void setTarget(StickMan & stickMan){target = &stickMan;}
};
#endif
