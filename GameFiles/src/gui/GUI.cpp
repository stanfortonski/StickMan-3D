/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#include "GUI.hpp"

GUI::GUI(Engine::Window & win, Engine::ShadersManager & aManager):
window(win), manager(aManager), fontRenderer(win, Font("fonts/Duo-Dunkel.ttf", 72))
{
  mainMenu.init(std::vector<Button>({
    Button(fontRenderer, "1 vs 1"),
    Button(fontRenderer, "vs NPC"),
    Button(fontRenderer, "Control"),
    Button(fontRenderer, "Exit")
  }));

  pauseMenu.init(std::vector<Button>({
    Button(fontRenderer, "Resume"),
    Button(fontRenderer, "Back to menu"),
    Button(fontRenderer, "Exit")
  }));

  currentMenu = &mainMenu;
  initMainMenu();
}

void GUI::initMainMenu()
{
  window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  pauseMenu.resetFocus();
  mainMenu.resetFocus();
  mainMenu.calcScaleAndPositions(window);
  currentMenu = &mainMenu;
}

void GUI::initPauseMenu()
{
  window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  mainMenu.resetFocus();
  pauseMenu.resetFocus();
  pauseMenu.calcScaleAndPositions(window);
  currentMenu = &pauseMenu;
}

void GUI::initCredits()
{
  window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  mainMenu.resetFocus();
  pauseMenu.resetFocus();
  currentMenu = nullptr;
}

void GUI::initFight()
{
  window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  mainMenu.resetFocus();
  pauseMenu.resetFocus();
  currentMenu = nullptr;
}

void GUI::renderFightInterface(const Fight & fight)
{
  float width = 0;
  float height = 0;
  float posY = window.getHeight() - 122.4;

  manager.getPostProcessProgram().use();
  if ((fight.getP1().getHP() < 10 && fight.getP1().getHP() > 0) || (fight.getP2().getHP() < 10 && fight.getP2().getHP() > 0))
    manager.getPostProcessProgram().setFloat("slowMotion", 0.3);
  else manager.getPostProcessProgram().setFloat("slowMotion", 1.0);

  if (fight.getState() == Fight::FIGHT)
  {
    fontRenderer.setScale(1.1);
    fontRenderer.setColor(glm::vec3(0.92, 0.64, 0.02));

    fontRenderer.setText(std::string(std::to_string(fight.getActualRound())+"/"+std::to_string(fight.getRoundsInTotal())));
    fontRenderer.getLineWidthAndHeight(width, height);
    fontRenderer.setPosition(window.getWidth()/2 - width/2, posY);
    fontRenderer.render(manager.getFontProgram());

    fontRenderer.setScale(0.6);
    fontRenderer.setColor(glm::vec3(0.77, 0.53, 0.04));

    fontRenderer.setText(std::string(std::to_string(fight.getP1sPoints())+" : "+std::to_string(fight.getP2sPoints())));
    fontRenderer.getLineWidthAndHeight(width, height);
    fontRenderer.setPosition(window.getWidth()/2 - width/2, posY - 67.2);
    fontRenderer.render(manager.getFontProgram());

    fontRenderer.setScale(1.1);
    fontRenderer.setColor(glm::vec3(0.1, 0.1, 0.1));
    float hp = fight.getP1().getHP();
    if (hp > 0 && hp < 1)
      hp = 1;

    fontRenderer.setText(std::string("HP: "+std::to_string((int)hp)));
    fontRenderer.getLineWidthAndHeight(width, height);
    fontRenderer.setPosition(window.getWidth()/4 - width/2, posY);
    fontRenderer.render(manager.getFontProgram());

    hp = fight.getP2().getHP();
    if (hp > 0 && hp < 1)
      hp = 1;

    fontRenderer.setText(std::string("HP: "+std::to_string((int)hp)));
    fontRenderer.getLineWidthAndHeight(width, height);
    fontRenderer.setPosition(window.getWidth() - window.getWidth()/4 - width/2, posY);
    fontRenderer.render(manager.getFontProgram());
  }

  if (fight.getMessage().length() > 0)
  {
    fontRenderer.setScale(1.3);
    fontRenderer.setColor(glm::vec3(0.98, 0.96, 0.01));
    fontRenderer.setText(fight.getMessage());
    fontRenderer.getLineWidthAndHeight(width, height);
    fontRenderer.setPosition(window.getWidth()/2 - width/2, window.getHeight()/2 - height/2);
    fontRenderer.render(manager.getFontProgram());
  }
}

void GUI::renderMainMenu()
{
  mainMenu.render(manager.getFontProgram());

  fontRenderer.setColor(glm::vec3(1.0, 1.0, 1.0));

  float offset = 72 * 0.5 + 20;
  fontRenderer.setScale(0.5);
  fontRenderer.setPosition(20, window.getHeight() - offset);
  fontRenderer.setText("StickMan 3D");
  fontRenderer.render(manager.getFontProgram());
  fontRenderer.setPosition(20, window.getHeight() - offset*2);
  fontRenderer.setText("First Round");
  fontRenderer.render(manager.getFontProgram());

  offset = 72 * 0.67;
  fontRenderer.setScale(0.3);
  fontRenderer.setPosition(window.getWidth() - offset*8, 12);
  fontRenderer.setText("By Stan Fortonski 2020");
  fontRenderer.render(manager.getFontProgram());
}

void GUI::renderAuthorCredits()
{
  std::vector<std::string> player1Control = {
    "* Control Player 1: ",
    "W, D - move forward",
    "A, S - move backward",
    "R - left punch",
    "T - right punch",
    "F - left kick",
    "G - right kick",
    "C - block punch",
    "V - block kick",
    "",
    "* Joystick: ",
    "1 - left punch",
    "2 - right punch",
    "3 - right kick",
    "4 - left kick"
  };

  std::vector<std::string> player2Control = {
    "* Control Player 2: ",
    "Arrow left/up - move forward",
    "Arrow right/down - move backward",
    "U - left punch",
    "I - right punch",
    "J - left kick",
    "K - right kick",
    "N - block punch",
    "M - block kick",
    "",
    "",
    "Arrows, left analog stick - move",
    "R1 - block punch",
    "L1 - block kick"
  };

  float offset = 72 * 0.6 + 5;
  fontRenderer.setScale(0.4);

  for (unsigned i = 0; i < player1Control.size(); ++i)
  {
    if (i == 0 || i == 10)
      fontRenderer.setColor(glm::vec3(0.8784, 0.8274, 0.0784));
    else fontRenderer.setColor(glm::vec3(1.0, 1.0, 1.0));
    fontRenderer.setPosition(window.getWidth()*0.125, window.getHeight()*0.9 - ((i+1) * offset));
    fontRenderer.setText(player1Control[i]);
    fontRenderer.render(manager.getFontProgram());
  }

  fontRenderer.setColor(glm::vec3(1.0, 1.0, 1.0));
  for (unsigned i = 0; i < player2Control.size(); ++i)
  {
    if (i == 0)
      fontRenderer.setColor(glm::vec3(0.8784, 0.8274, 0.0784));
    else fontRenderer.setColor(glm::vec3(1.0, 1.0, 1.0));
    fontRenderer.setText(player2Control[i]);
    fontRenderer.setPosition(window.getWidth()*0.5, window.getHeight()*0.9 - ((i+1) * offset));
    fontRenderer.render(manager.getFontProgram());
  }

  fontRenderer.setColor(glm::vec3(0.8784, 0.8274, 0.0784));
  fontRenderer.setText("Press ESC/Start for back");
  fontRenderer.setPosition(window.getWidth() - offset*13, offset);
  fontRenderer.render(manager.getFontProgram());
}

void GUI::renderPauseMenu()
{
  manager.getPostProcessProgram().use();
  manager.getPostProcessProgram().setFloat("slowMotion", 1.0);
  pauseMenu.render(manager.getFontProgram());
}

void GUI::checkHoverOfButtons(const double & posX, const double & posY)
{
  if (currentMenu != nullptr)
    currentMenu->checkHoverOfButtons(posX, posY);
}

void GUI::calcScaleAndPositions()
{
  if (currentMenu != nullptr)
    currentMenu->calcScaleAndPositions(window);
}

void GUI::focusPrevButton()
{
  if (currentMenu != nullptr)
    currentMenu->focusPrevButton();
}

void GUI::focusNextButton()
{
  if (currentMenu != nullptr)
    currentMenu->focusNextButton();
}

int GUI::getFocusButtonId()
{
  if (currentMenu != nullptr)
    return currentMenu->getFocusButtonId();
  return -1;
}
