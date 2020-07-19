/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#include "StickManAnims.hpp"

StickManAnims::StickManAnims(const float & aWalkSpeed): ModelAnim("objects/stickman/stickman.fbx"), walkSpeed(aWalkSpeed){;}

void StickManAnims::playStayAnim()
{
  name = "stay";
  play(300, 320);
  setLoop(true);
  setSpeed(0.25);
}

void StickManAnims::playStartWalkAnim()
{
  name = "start_walk";
  play(350, 358);
  setLoop(false);
  setSpeed(walkSpeed);
}

void StickManAnims::playEndWalkAnim()
{
  name = "end_walk";
  float duration = getAnimationDuration();
  if (duration/2 <= getCurrentTick() - getStartTick())
    play(getCurrentTick(), 390);
  else play(getCurrentTick(), 350);
  setLoop(false);
  setSpeed(walkSpeed);
}

void StickManAnims::playWalkAnim()
{
  name = "walk";
  play(358, 382);
  setLoop(true);
  setSpeed(walkSpeed);
}

void StickManAnims::playGoLeftAnim()
{
  name = "go_left";
  play(390, 410);
  setLoop(false);
  setSpeed(0.75);
}

void StickManAnims::playGoRightAnim()
{
  name = "go_right";
  play(410, 430);
  setLoop(false);
  setSpeed(0.6);
}

void StickManAnims::playLeftPunchAnim()
{
  name = "left_punch";
  play(40, 70);
  setLoop(false);
  setSpeed(0.95);
}

void StickManAnims::playRightPunchAnim()
{
  name = "right_punch";
  play(0, 40);
  setLoop(false);
  setSpeed(0.5);
}

void StickManAnims::playLeftKickAnim()
{
  name = "left_kick";
  play(70, 90);
  setLoop(false);
  setSpeed(0.8);
}

void StickManAnims::playRightKickAnim()
{
  name = "right_kick";
  play(90, 110);
  setLoop(false);
  setSpeed(0.83);
}

void StickManAnims::playKickDefenseAnim()
{
  name = "kick_defense";
  play(260, 280);
  setLoop(false);
  setSpeed(0.6);
}

void StickManAnims::playPunchDefenseAnim()
{
  name = "punch_defense";
  play(110, 130);
  setLoop(false);
  setSpeed(0.75);
}

void StickManAnims::playDeadAnim()
{
  name = "dead";
  play(130, 160);
  setLoop(false);
  setSpeed(0.6);
}

void StickManAnims::playLieAnim()
{
  name = "lie";
  play(159, 160);
  setLoop(true);
  setSpeed(0.6);
}

void StickManAnims::playWelcomeAnim()
{
  name = "welcome";
  play(170, 190);
  setLoop(false);
  setSpeed(0.3);
}

void StickManAnims::playWinAnim()
{
  name = "win";
  play(190, 230);
  setLoop(true);
  setSpeed(0.52);
}

void StickManAnims::playLoseAnim()
{
  name = "lose";
  play(230, 260);
  setLoop(false);
  setSpeed(0.4);
}

void StickManAnims::playKickedAnim()
{
  name = "kicked";
  play(320, 350);
  setLoop(false);
  setSpeed(1.0);
}

void StickManAnims::playPunchedAnim()
{
  name = "punched";
  play(280, 300);
  setLoop(false);
  setSpeed(0.7);
}
