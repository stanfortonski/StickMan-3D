/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#include "Button.hpp"

void Button::calcWidthAndHeight()
{
  width = 0;
  height = 0;
  fontRenderer->setScale(scale);
  fontRenderer->setText(label);
  fontRenderer->getLineWidthAndHeight(width, height);
}

bool Button::isHover(const double & posX, const double & posY) const
{
  if (pos.x <= posX && (pos.x + width) >= posX)
  {
    if (pos.y <= posY && (pos.y + height) >= posY)
      return true;
  }
  return false;
}

void Button::checkHover(const double & posX, const double & posY)
{
  if (isHover(posX, posY))
    hovered = true;
  else hovered = false;
}

void Button::render(Engine::Program & program)
{
  if (hovered)
    fontRenderer->setColor(glm::vec3(0.3f, 1.0f, 0.3f));
  else fontRenderer->setColor(glm::vec3(1.0f, 0.3f, 0.3f));

  fontRenderer->setPosition(pos.x, pos.y);
  fontRenderer->setScale(scale);
  fontRenderer->setText(label);
  fontRenderer->render(program);
}
