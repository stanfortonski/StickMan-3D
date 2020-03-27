/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#ifndef STICKMAN_ANIMS_HPP
#define STICKMAN_ANIMS_HPP 1
#include "../../../src/engine/include.hpp"

using namespace Engine;

class StickManAnims: public ModelAnim
{
  std::string name;
  float walkSpeed;

public:
  StickManAnims(const float & aWalkSpeed = 0.6f);

  void playStayAnim();
  void playStartWalkAnim();
  void playEndWalkAnim();
  void playWalkAnim();
  void playJumpAnim();
  void playGoLeftAnim();
  void playGoRightAnim();
  void playLeftPunchAnim();
  void playRightPunchAnim();
  void playLeftKickAnim();
  void playRightKickAnim();
  void playKickDefenseAnim();
  void playPunchDefenseAnim();
  void playDeadAnim();
  void playLieAnim();
  void playWelcomeAnim();
  void playWinAnim();
  void playLoseAnim();
  void playKickedAnim();
  void playPunchedAnim();

  std::string getAnimName() const{return name;}
  bool isAnimPlay(const std::string & n) const{return name == n;}

  float getMoveAnimSpeed() const{return walkSpeed;}
  void setMoveAnimSpeed(const float & speed){walkSpeed = speed;}
};
#endif
