/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#include "Fight.hpp"

Fight::Fight(FightCamera & cam, StickMan & stickMan1, StickMan & stickMan2): camera(cam), p1(stickMan1), p2(stickMan2)
{
  init();

  p1.setTarget(p2);
  p2.setTarget(p1);
  p2.rotateY(180);

  totalRounds = 2;
  actualRound = 1;
  points1 = 0;
  points2 = 0;
  waitTime = 0;
  messageTime = 0;
  state = WELCOME;
}

void Fight::init()
{
  p1.init();
  p2.init();

  p1.translate(glm::vec3(-2.0f, 0.0f, 0.0f));
  p2.translate(glm::vec3(2.0f, 0.0f, 0.0f));
  p2.invertDirection();
}

void Fight::checkMessage()
{
  if (messageTime != 0 && glfwGetTime() >= messageTime)
  {
    messageTime = 0;
    message = "";
  }
}

void Fight::showLoseP1()
{
  message = "P1 LOSE";
  messageTime = glfwGetTime() + 2;
  camera.setFaceView1();
  p1.playLoseAnim();
}

void Fight::showLoseP2()
{
  message = "P2 LOSE";
  messageTime = glfwGetTime() + 2;
  camera.setFaceView2();
  p2.playLoseAnim();
}

void Fight::showWinP1()
{
  message = "P1 WIN";
  messageTime = glfwGetTime() + 4;
  camera.setFaceView1();
  p1.playWinAnim();
}

void Fight::showWinP2()
{
  message = "P2 WIN";
  messageTime = glfwGetTime() + 4;
  camera.setFaceView2();
  p2.playWinAnim();
}

void Fight::processWelcome()
{
  p1.playWelcomeAnim();
  p2.playWelcomeAnim();
  state = WAIT_FOR_NEXT_ROUND;
}

void Fight::checkRoute()
{
  if (++actualRound > totalRounds)
  {
    if (points1 != points2)
    {
      actualRound -= 1;
      state = WIN_SHOW;
      return;
    }
  }
  state = WAIT_AFTER_LOSE;
}

void Fight::processCheckResult()
{
  if (p1.hasNoHP() && p2.hasNoHP())
  {
    ++points1;
    ++points2;
    init();
  }
  else if (p1.hasNoHP())
  {
    ++points2;
    init();
    showLoseP1();
  }
  else if (p2.hasNoHP())
  {
    ++points1;
    init();
    showLoseP2();
  }
  checkRoute();
}

void Fight::processWaitAfterLose()
{
  if (waitTime == 0)
  {
    waitTime = glfwGetTime() + 2;
  }
  else if (glfwGetTime() >= waitTime)
  {
    state = WAIT_FOR_NEXT_ROUND;
    waitTime = 0;
  }
}

void Fight::processWaitForNextRound()
{
  if (waitTime == 0)
  {
    waitTime = glfwGetTime() + 4;
    messageTime = waitTime;
  }
  else if (glfwGetTime() >= waitTime)
  {
    state = FIGHT;
    waitTime = 0;
  }
  int time = waitTime - glfwGetTime();
  if (time <= 0)
    message = "FIGHT";
  else message = std::to_string(time);
}

void Fight::processFight()
{
  if (p1.hasNoHP() || p2.hasNoHP())
  {
    if (waitTime == 0)
    {
      waitTime = glfwGetTime() + 3;
    }
    else if (glfwGetTime() >= waitTime)
    {
      state = CHECK_RESULT;
      waitTime = 0;
    }
  }
  else
  {
    p1.think();
    p2.think();
  }
}

void Fight::processEndFight()
{
  if (waitTime == 0)
  {
    waitTime = glfwGetTime() + 4;
    init();
    if (points1 > points2)
      showWinP1();
    else showWinP2();
  }
  else if (glfwGetTime() >= waitTime)
    state = ENDED;
}

void Fight::fight()
{
  switch (state)
  {
    case WELCOME:
      camera.setFightView(p1);
      processWelcome();
    break;

    case CHECK_RESULT:
      processCheckResult();
    break;

    case WAIT_AFTER_LOSE:
      processWaitAfterLose();
    break;

    case WAIT_FOR_NEXT_ROUND:
      camera.setFightView(p1);
      processWaitForNextRound();
    break;

    case FIGHT:
      camera.setFightView(p1);
      processFight();
    break;

    case WIN_SHOW:
      processEndFight();
    break;
  }
  checkMessage();
}
