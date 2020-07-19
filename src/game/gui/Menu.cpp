/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#include "GUI.hpp"

void Menu::render(Engine::Program & program)
{
  for (unsigned i = 0; i < buttons.size(); ++i)
    buttons[i].render(program);
}

void Menu::checkHoverOfButtons(const double & posX, const double & posY)
{
  focusButton = -1;
  for (unsigned i = 0; i < buttons.size(); ++i)
  {
    buttons[i].checkHover(posX, posY);
    if (buttons[i].isFocus())
      focusButton = i+1;
  }
}

void Menu::calcScaleAndPositions(Window & window)
{
  float scale = ((float)window.getWidth()/(float)window.getHeight()) * 0.65f;
  float halfWindow = window.getWidth()/2.0f;
  float yAlign = window.getHeight();
  float yPadding = ((float)window.getHeight()/(float)buttons.size());

  for (unsigned i = 0; i < buttons.size(); ++i)
  {
    buttons[i].setScale(scale);
    float xAlign = halfWindow - buttons[i].getWidth()/2;
    yAlign -= buttons[i].getHeight() + yPadding/2;
    buttons[i].setPosition(glm::vec2(xAlign, yAlign+buttons[i].getHeight()*0.35f));
  }
}

void Menu::resetFocus()
{
  for (int i = 0; i < buttons.size(); ++i)
    buttons[i].setFocus(false);
  focusButton = -1;
}

void Menu::getFocusButton(int id)
{
  for (int i = 0; i < buttons.size(); ++i)
    buttons[i].setFocus(false);
  buttons[id].setFocus(true);
}

void Menu::focusPrevButton()
{
  if (focusButton == -1)
    focusButton = 1;
  else if (focusButton == 1)
    focusButton = buttons.size();
  else --focusButton;
  getFocusButton(focusButton - 1);
}

void Menu::focusNextButton()
{
  if (focusButton == -1)
    focusButton = 1;
  else if (focusButton == buttons.size())
    focusButton = 1;
  else ++focusButton;

  getFocusButton(focusButton - 1);
}
