/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#include "Game.hpp"

bool GameInput::isClickedEnter() const
{
  GLFWwindow * win = game.window.getWindowPointer();
  return glfwGetKey(win, GLFW_KEY_ENTER) == GLFW_PRESS || glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
}

bool GameInput::canFightControl() const
{
  if (game.fight == nullptr)
    return false;
  return game.fight->getState() == Fight::FIGHT;
}

void GameInput::switchingMainMenu()
{
  switch (game.gui->getFocusButtonId())
  {
    case 1:
    {
      game.appMode = game.FIGHT_MODE;
      game.fightMode = game.PVP_MODE;
      game.initFight();
      game.gui->initFight();
    }
    break;

    case 2:
    {
      game.appMode = game.FIGHT_MODE;
      game.fightMode = game.PVN_MODE;
      game.initFight();
      game.gui->initFight();
    }
    break;

    case 3:
    {
      game.appMode = game.CREDITS_MODE;
      game.gui->initCredits();
    }
    break;

    case 4:
      game.window.stopRender();
    break;
  }
}

void GameInput::switchingPauseMenu()
{
  switch (game.gui->getFocusButtonId())
  {
    case 1:
    {
      if (game.fight->getState() == Fight::ENDED)
      {
        game.clearForFight();
        game.initFight();
      }
      game.appMode = game.FIGHT_MODE;
      game.gui->initFight();
    }
    break;

    case 2:
    {
      game.appMode = game.MENU_MODE;
      game.clearForFight();
      game.gui->initMainMenu();
    }
    break;

    case 3:
      game.window.stopRender();
    break;
  }
}

bool GameInput::initJoystickForFight(int type, StickMan * player, bool reverse)
{
  if (glfwJoystickPresent(type) == 1)
  {
    int axesCount;
    int buttonsCount;
    const float * axes = glfwGetJoystickAxes(type, &axesCount);
    const unsigned char * buttons = glfwGetJoystickButtons(type, &buttonsCount);
    float leftTriggerX = round(axes[0]);
    float leftTriggerY = round(axes[1]);

    if (reverse)
    {
      if (leftTriggerY == -1 || leftTriggerX == 1 || buttons[13] == GLFW_PRESS || buttons[12] == GLFW_PRESS)
        player->backwardWalk();
      else if (leftTriggerY == 1 || leftTriggerX == -1 || buttons[15] == GLFW_PRESS || buttons[14] == GLFW_PRESS)
        player->forwardWalk();
    }
    else
    {
      if (leftTriggerY == -1 || leftTriggerX == 1 || buttons[13] == GLFW_PRESS || buttons[12] == GLFW_PRESS)
        player->forwardWalk();
      else if (leftTriggerY == 1 || leftTriggerX == -1 || buttons[15] == GLFW_PRESS || buttons[14] == GLFW_PRESS)
        player->backwardWalk();
    }

    if (buttons[0] == GLFW_PRESS)
      player->leftPunch();
    else if (buttons[1] == GLFW_PRESS)
      player->rightPunch();
    if (buttons[2] == GLFW_PRESS)
      player->rightKick();
    else if (buttons[3] == GLFW_PRESS)
      player->leftKick();
    if (buttons[5] == GLFW_PRESS)
      player->punchDefense();
    else if (buttons[4] == GLFW_PRESS)
      player->kickDefense();
    else if (buttons[8] == GLFW_PRESS)
    {
      game.appMode = game.PAUSE_MODE;
      game.gui->initPauseMenu();
    }
    return true;
  }
  return false;
}

bool GameInput::initJoystickForMenu(int type)
{
  static double endLockTime = 0;
  if (glfwJoystickPresent(type) == 1)
  {
    int buttonsCount;
    const unsigned char * buttons = glfwGetJoystickButtons(type, &buttonsCount);

    if (game.appMode == game.MENU_MODE)
    {
      if (buttons[2] == GLFW_PRESS)
        switchingMainMenu();
    }
    else if (game.appMode == game.PAUSE_MODE)
    {
      if (buttons[9] == GLFW_PRESS)
      {
        game.appMode = game.FIGHT_MODE;
        game.gui->initFight();
      }
      else if (buttons[2] == GLFW_PRESS)
        switchingPauseMenu();
    }

    double time = glfwGetTime();
    if (buttons[12] == GLFW_PRESS && endLockTime <= time)
    {
      endLockTime = time + 0.4;
      game.gui->focusPrevButton();
    }
    else if (buttons[14] == GLFW_PRESS && endLockTime <= time)
    {
      endLockTime = time + 0.4;
      game.gui->focusNextButton();
    }
    return true;
  }
  return false;
}

bool GameInput::initJoystickForCredits(int type)
{
  if (glfwJoystickPresent(type) == 1)
  {
    int buttonsCount;
    const unsigned char * buttons = glfwGetJoystickButtons(type, &buttonsCount);

    if (buttons[9] == GLFW_PRESS)
    {
      game.appMode = game.MENU_MODE;
      game.gui->initMainMenu();
    }
    return true;
  }
  return false;
}

void GameInput::initPlayer1AttacksOnKeyBoard(int key, int action)
{
  if (canFightControl() && action == GLFW_PRESS)
  {
    switch (key)
    {
      case GLFW_KEY_R:
        game.player1->leftPunch();
      break;

      case GLFW_KEY_T:
        game.player1->rightPunch();
      break;

      case GLFW_KEY_F:
        game.player1->leftKick();
      break;

      case GLFW_KEY_G:
        game.player1->rightKick();
      break;

      case GLFW_KEY_C:
        game.player1->punchDefense();
      break;

      case GLFW_KEY_V:
        game.player1->kickDefense();
      break;
    }
  }
}

void GameInput::initPlayer2AttacksOnKeyBoard(int key, int action)
{
  if (canFightControl() && action == GLFW_PRESS)
  {
    switch (key)
    {
      case GLFW_KEY_U:
        game.player2->leftPunch();
      break;

      case GLFW_KEY_I:
        game.player2->rightPunch();
      break;

      case GLFW_KEY_J:
        game.player2->leftKick();
      break;

      case GLFW_KEY_K:
        game.player2->rightKick();
      break;

      case GLFW_KEY_N:
        game.player2->punchDefense();
      break;

      case GLFW_KEY_M:
        game.player2->kickDefense();
      break;
    }
  }
}

void GameInput::initPlayer1MoveOnKeyBoard()
{
  if (!game.player1->hasNoHP())
  {
    GLFWwindow * win = game.window.getWindowPointer();
    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
      game.player1->forwardWalk();
    else if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
      game.player1->backwardWalk();
  }
}

void GameInput::initPlayer2MoveOnKeyBoard()
{
  if (!game.player2->hasNoHP())
  {
    GLFWwindow * win = game.window.getWindowPointer();
    if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS)
      game.player2->forwardWalk();
    else if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS)
      game.player2->backwardWalk();
  }
}

void GameInput::PVNInputs()
{
  if (canFightControl())
  {
    if (!game.player1->hasNoHP())
    {
      isJoyStick1Connected = initJoystickForFight(GLFW_JOYSTICK_1, game.player1);
      if (!isJoyStick1Connected)
        initPlayer1MoveOnKeyBoard();
    }
  }
}

void GameInput::PVPInputs()
{
  if (canFightControl())
  {
    if (!game.player1->hasNoHP())
    {
      isJoyStick1Connected = initJoystickForFight(GLFW_JOYSTICK_1, game.player1);
      if (!isJoyStick1Connected)
        initPlayer1MoveOnKeyBoard();
    }

    if (!game.player2->hasNoHP())
    {
      isJoyStick2Connected = initJoystickForFight(GLFW_JOYSTICK_2, game.player2, true);
      if (!isJoyStick2Connected)
        initPlayer2MoveOnKeyBoard();
    }
  }
}

void GameInput::mainMenuInputs()
{
  initJoystickForMenu(GLFW_JOYSTICK_1);
  initJoystickForMenu(GLFW_JOYSTICK_2);
  if (isClickedEnter())
    switchingMainMenu();
}

void GameInput::pauseMenuInputs()
{
  initJoystickForMenu(GLFW_JOYSTICK_1);
  initJoystickForMenu(GLFW_JOYSTICK_2);
  if (isClickedEnter())
    switchingPauseMenu();
}

void GameInput::creditsInputs()
{
  initJoystickForCredits(GLFW_JOYSTICK_1);
  initJoystickForCredits(GLFW_JOYSTICK_2);
}

void GameInput::processInput()
{
  if (game.appMode == game.MENU_MODE)
    mainMenuInputs();
  else if (game.appMode == game.PAUSE_MODE)
    pauseMenuInputs();
  else if (game.appMode == game.CREDITS_MODE)
      creditsInputs();
  else if (game.appMode == game.FIGHT_MODE)
  {
    if (game.fightMode == game.PVN_MODE)
      PVNInputs();
    else if (game.fightMode == game.PVP_MODE)
      PVPInputs();
  }
}

void GameInput::mouseMove(const double & posX, const double & posY)
{
  if (game.appMode == game.MENU_MODE || game.appMode == game.PAUSE_MODE)
    game.gui->checkHoverOfButtons(posX, game.window.getHeight() - posY);
}

void GameInput::keyPress(int key, int scancode, int action, int mods)
{
  if (game.appMode == game.FIGHT_MODE)
  {
    if (game.fightMode == game.PVN_MODE && !isJoyStick1Connected)
      initPlayer1AttacksOnKeyBoard(key, action);
    else if (game.fightMode == game.PVP_MODE)
    {
      if (!isJoyStick1Connected)
        initPlayer1AttacksOnKeyBoard(key, action);

      if (!isJoyStick2Connected)
        initPlayer2AttacksOnKeyBoard(key, action);
    }
  }
  else if (game.appMode == game.MENU_MODE || game.appMode == game.PAUSE_MODE)
  {
    if (action == GLFW_RELEASE)
    {
      if (key == GLFW_KEY_UP)
        game.gui->focusPrevButton();
      else if (key == GLFW_KEY_DOWN)
        game.gui->focusNextButton();
    }
  }

  if (game.appMode != game.MENU_MODE && key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    switch (game.appMode)
    {
      case game.FIGHT_MODE:
      {
        game.appMode = game.PAUSE_MODE;
        game.gui->initPauseMenu();
      }
      break;

      case game.CREDITS_MODE:
      {
        game.appMode = game.MENU_MODE;
        game.gui->initMainMenu();
      }
      break;

      case game.PAUSE_MODE:
      {
        game.appMode = game.FIGHT_MODE;
        game.gui->initFight();
      }
      break;
    }
  }
}
