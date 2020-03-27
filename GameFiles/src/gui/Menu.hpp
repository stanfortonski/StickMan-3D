/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#ifndef MENU_HPP
#define MENU_HPP 1
#include "Button.hpp"

class Menu: public Engine::Renderable
{
  std::vector<Button> buttons;
  int focusButton = -1;

  void getFocusButton(int id);

public:
  Menu(){;}
  Menu(const std::vector<Button> & aButtons): buttons(aButtons){;}
  void init(const std::vector<Button> & aButtons){buttons = aButtons;}

  virtual void render(Engine::Program & program);

  void checkHoverOfButtons(const double & posX, const double & posY);
  void calcScaleAndPositions(Window & window);

  void resetFocus();
  void focusPrevButton();
  void focusNextButton();
  int getFocusButtonId() const{return focusButton;}
};
#endif
