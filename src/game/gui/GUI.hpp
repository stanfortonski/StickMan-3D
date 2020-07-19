/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#ifndef GUI_HPP
#define GUI_HPP 1
#include "../../../src/engine/Engine.hpp"
#include "../../../src/engine/renderable/shape/Plane.hpp"
#include "../../../src/engine/base/ShadersManager.hpp"
#include "../Fight.hpp"
#include "Menu.hpp"

class GUI
{
  Engine::Window & window;
  Engine::ShadersManager & manager;
  Engine::FontRenderer fontRenderer;

  Menu pauseMenu;
  Menu mainMenu;
  Menu * currentMenu = nullptr;

public:
  GUI(Engine::Window & win, Engine::ShadersManager & aManager);

  void initMainMenu();
  void initPauseMenu();
  void initCredits();
  void initFight();

  void renderFightInterface(const Fight & fight);
  void renderMainMenu();
  void renderPauseMenu();
  void renderAuthorCredits();

  void checkHoverOfButtons(const double & posX, const double & posY);
  void calcScaleAndPositions();

  void focusPrevButton();
  void focusNextButton();
  int getFocusButtonId();
};
#endif
