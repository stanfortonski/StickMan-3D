/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#include "StickManModel.hpp"

void StickManModel::init()
{
  setPosition(glm::vec3(0.0f, 0.48f, 0.0f));
  scale(glm::vec3(0.1f));
  playStayAnim();
  isLock = false;
  isWalking = false;
  isAttacking = false;
  isKickBlocking = false;
  isPunchBlocking = false;
  isKilled = false;
  walkEndTime = 0;
  direction = 1;
}

void StickManModel::update()
{
  bool isAnimEnd = isAnimationEnd();
  if (isAnimPlay("lie") || (isAnimEnd && isKilled && isAnimPlay("dead")))
  {
    playLieAnim();
  }
  else
  {
    if (isAnimEnd && !isLoop() & !(isAnimPlay("start_walk") || isAnimPlay("end_walk") || isAnimPlay("walk")))
    {
      isLock = false;
      isAttacking = false;
      isPunchBlocking = false;
      isKickBlocking = false;
      isWalking = false;
      playStayAnim();
    }

    if (isWalking)
    {
      if (isAnimPlay("start_walk") && isAnimEnd)
      {
        playWalkAnim();
        walkEndTime = glfwGetTime() + tickToTimeInSec(4) * getSpeed();
      }
      else if (isAnimPlay("end_walk") && isAnimEnd)
      {
        playStayAnim();
        isWalking = false;
      }
      else if (isAnimPlay("end_walk"))
      {
        isLock = false;
      }
      else
      {
        if (walkEndTime <= glfwGetTime() && isAnimPlay("walk"))
          playEndWalkAnim();
      }
    }
  }
}

void StickManModel::walk()
{
  if (!isWalking)
  {
    playStartWalkAnim();
    isWalking = true;
    isLock = true;
  }
  walkEndTime = glfwGetTime() + tickToTimeInSec(4) * getSpeed();
}

void StickManModel::forwardWalk()
{
  walk();
  translateForward();
}

void StickManModel::backwardWalk()
{
  walk();
  translateBackward();
}

void StickManModel::translateForward()
{
  translate(glm::vec3(moveSpeed * direction, 0.0f, 0.0f));
}

void StickManModel::translateBackward()
{
  translate(glm::vec3(-moveSpeed * direction, 0.0f, 0.0f));
}

void StickManModel::leftPunch()
{
  if (!isLock)
  {
    playLeftPunchAnim();
    isLock = true;
    isAttacking = true;
  }
}

void StickManModel::rightPunch()
{
  if (!isLock)
  {
    playRightPunchAnim();
    isLock = true;
    isAttacking = true;
  }
}

void StickManModel::leftKick()
{
  if (!isLock)
  {
    playLeftKickAnim();
    isLock = true;
    isAttacking = true;
  }
}

void StickManModel::rightKick()
{
  if (!isLock)
  {
    playRightKickAnim();
    isLock = true;
    isAttacking = true;
  }
}

void StickManModel::kickDefense()
{
  if (!isLock)
  {
    playKickDefenseAnim();
    isLock = true;
    isKickBlocking = true;
  }
}

void StickManModel::punchDefense()
{
  if (!isLock)
  {
    playPunchDefenseAnim();
    isLock = true;
    isPunchBlocking = true;
  }
}

void StickManModel::dead()
{
  playDeadAnim();
  translate(glm::vec3(0.0f, -0.04f, 0.0f));
  isKilled = true;
}

void StickManModel::kicked()
{
  playKickedAnim();
  isLock = true;
}

void StickManModel::punched()
{
  playPunchedAnim();
  isLock = true;
}
