/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#ifndef GAME_HPP
#define GAME_HPP 1
#include "../../src/engine/include.hpp"
#include "FightCamera.hpp"
#include "RainEffect.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "Fight.hpp"
#include "gui/GUI.hpp"

class Game;

class GameInput
{
  Game & game;
  bool firstTime = true;
  float lastPosX = 0;
  float lastPosY = 0;
  bool isJoyStick1Connected = false;
  bool isJoyStick2Connected = false;

  bool isClickedEnter() const;
  bool canFightControl() const;
  void switchingMainMenu();
  void switchingPauseMenu();
  bool initJoystickForFight(int type, StickMan * player, bool reverse = false);
  bool initJoystickForMenu(int type);
  bool initJoystickForCredits(int type);
  void initPlayer1AttacksOnKeyBoard(int key, int action);
  void initPlayer2AttacksOnKeyBoard(int key, int action);
  void initPlayer1MoveOnKeyBoard();
  void initPlayer2MoveOnKeyBoard();
  void PVNInputs();
  void PVPInputs();
  void mainMenuInputs();
  void pauseMenuInputs();
  void creditsInputs();

public:
  explicit GameInput(Game & g): game(g){;}

  void processInput();
  void mouseMove(const double & posX, const double & posY);
  void keyPress(int key, int scancode, int action, int mods);
};

class Game
{
  friend class GameInput;

  enum {MENU_MODE = 1, FIGHT_MODE = 2, CREDITS_MODE = 3, PAUSE_MODE = 4, PVN_MODE = 5, PVP_MODE = 6};
  unsigned appMode = MENU_MODE;
  unsigned fightMode;

  GameInput * input;
  Window & window;
  ShadersManager manager;
  GUI * gui;
  Program * interfaceProgram;
  InterfaceCamera * camera;
  FightCamera perspectiveCamera;
  Skybox skybox;
  Scene * scene;
  Model worldModel;
  RainEffect * rain;
  Light pointLight;
  Bloom bloomEffect;
  PostProcessing postHDR;
  PostProcessing post;

  Fight * fight = nullptr;
  Player * player1 = nullptr;
  StickMan * player2 = nullptr;

  void initShadersManager();
  void initOnlyMap();
  void initFight();
  void clearForFight();

public:
  Game(Window & win);
  virtual ~Game();

  void render();
  void processInput();
  void mouseMove(const double & posX, const double & posY);
  void keyPress(int key, int scancode, int action, int mods);
};
#endif
