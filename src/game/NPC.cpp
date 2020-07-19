/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#include "NPC.hpp"

NPC::NPC()
{
  Material material(glm::vec3(0.2f, 0.01f, 0.01f), glm::vec3(0.4f, 0.1f, 0.1f), glm::vec3(0.41f, 0.11f, 0.11f), 2);
  changeWholeMaterial(material);
  randomPersonality();
  work = 1;
  timeToEndWork = 0;
}

void NPC::randomPersonality()
{
  hpToDefMode = rand()%40+1;
  procentageDefOrOff = rand()%100+1;
  procentageWalkWait = rand()%30+1;
  procentageAttackWait = rand()%20+1;
  distanceOffensive = (float)(rand()%50)/100.0f + 0.56f;
  distanceDefensive = (float)(rand()%40)/100.0f + 0.75f;
}

void NPC::think()
{
  double time = glfwGetTime();
  if (time >= timeToEndWork)
  {
    timeToEndWork = time + DELAY_TIME;
    if (getHP() < hpToDefMode)
      playDefensive();
    else playOffensive();
  }
  chooseWork();
}

void NPC::playOffensive()
{
  if (isRangeOffensive())
  {
    int whatToDo = rand()%100+1;
    if (procentageDefOrOff <= whatToDo)
    {
      if (!wait(procentageAttackWait))
        randomAttackBasedOnRange();
    }
    else defensive();
  }
  else
  {
    if (!wait(procentageWalkWait))
      work = 0;
  }
}

void NPC::playDefensive()
{
  int whatToDo = rand()%3+1;
  if (whatToDo == 1)
    work = 7;
  else if (whatToDo == 2)
    defensive();
  else if (whatToDo == 3)
    randomAttackBasedOnRange();
}

bool NPC::wait(const int & procent)
{
  int waitProc = rand()%100+1;
  if (waitProc <= procent)
  {
    float timeInSec = (float)(rand()%200)/100.0f;
    timeToEndWork = glfwGetTime() + timeInSec;
    work = -1;
    return true;
  }
  return false;
}

void NPC::defensive()
{
  if (target->isWhileKicking())
    work = 5;
  else if (target->isWhilePunching())
    work = 6;
  else timeToEndWork = 0;
}

void NPC::randomAttackBasedOnRange()
{
  if (isRightKickRange())
    work = rand()%4+1;
  else if (isLeftPunchRange())
    work = rand()%3+1;
  else if (isLeftKickRange())
    work = rand()%2+1;
  else if (isRightPunchRange())
    work = 1;
  else timeToEndWork = 0;
}

void NPC::chooseWork()
{
  switch (work)
  {
    case 0:
    {
      if (!isRangeOffensive())
        forwardWalk();
      else timeToEndWork = 0;
    }
    break;

    case 1:
      rightPunch();
    break;

    case 2:
      leftKick();
    break;

    case 3:
      leftPunch();
    break;

    case 4:
      rightKick();
    break;

    case 5:
      if (getDistanceBetween().x < 0.95f)
        kickDefense();
      else timeToEndWork = 0;
    break;

    case 6:
      if (getDistanceBetween().x < 1.175f)
        punchDefense();
      else timeToEndWork = 0;
    break;

    case 7:
    {
      if (isRangeDefensive())
        backwardWalk();
      else timeToEndWork = 0;
    }
    break;
  }
}
