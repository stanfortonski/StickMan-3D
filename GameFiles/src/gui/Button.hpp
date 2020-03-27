/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#ifndef BUTTON_HPP
#define BUTTON_HPP 1
#include <glm/glm.hpp>
#include "../../../src/engine/renderable/shape/Plane.hpp"
#include "../../../src/engine/renderable/font/FontRenderer.hpp"

class Button: Engine::Renderable
{
  Engine::FontRenderer * fontRenderer;
  glm::vec2 pos;
  float scale;
  float width;
  float height;
  std::string label;
  bool hovered = false;

  void calcWidthAndHeight();
  bool isHover(const double & posX, const double & posY) const;

public:
  Button(Engine::FontRenderer & aFontRenderer, const std::string & aLabel = "", const int & aScale = 1.0, const float & posX = 0.0, const float & posY = 0.0):
  fontRenderer(&aFontRenderer), pos(glm::ivec2(posX, posY)), label(aLabel){setScale(aScale);}

  virtual void render(Engine::Program & program);

  bool isFocus() const{return hovered;}
  void setFocus(bool val){hovered = val;}
  void checkHover(const double & posX, const double & posY);

  void setPosition(const glm::vec2 & aPos){pos = aPos;}
  glm::vec2 getPosition() const{return pos;}

  void setScale(const float & aScale){scale = aScale; calcWidthAndHeight();}
  float getScale() const{return scale;}

  void setLabel(const std::string & aLabel){label = aLabel;}
  std::string getLabel() const{return label;}

  float getHeight() const{return height;}
  float getWidth() const{return width;}

  void setHeight(const float & h){height = h;}
  void setWidth(const float & w){width = w;}
};
#endif
