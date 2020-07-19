/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#ifndef STICKMAN_MODEL_HPP
#define STICKMAN_MODEL_HPP 1
#include "StickManAnims.hpp"

class StickManModel: public StickManAnims
{
  bool isLock;
  bool isWalking;
  bool isAttacking;
  bool isPunchBlocking;
  bool isKickBlocking;
  bool isKilled;
  float walkEndTime;
  int direction;
  float moveSpeed;

  void walk();

public:
  StickManModel(const float & aMoveSpeed = 0.0175f): moveSpeed(aMoveSpeed){rotateY(-90);}

  virtual void init();
  virtual void update();
  virtual void forwardWalk();
  virtual void backwardWalk();
  void leftPunch();
  void rightPunch();
  void leftKick();
  void rightKick();
  void kickDefense();
  void punchDefense();

  void punched();
  void kicked();
  void translateForward();
  void translateBackward();
  void dead();

  bool isDead() const{return isKilled;}
  bool isAlive() const{return !isKilled;}
  bool isInStay() const{return !isWalking;}
  bool isInWalk() const{return isWalking;}
  bool isInAttacking() const{return isAttacking;}
  bool isInKickBlocking() const{return isKickBlocking;}
  bool isInPunchBlocking() const{return isPunchBlocking;}
  void invertDirection(){direction = -direction;}
  int getDirection() const{return direction;}
  float getMoveSpeed() const{return moveSpeed;}
  void setMoveSpeed(const float & aMoveSpeed){moveSpeed = aMoveSpeed;}
};
#endif
