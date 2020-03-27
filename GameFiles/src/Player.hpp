/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#ifndef PLAYER_HPP
#define PLAYER_HPP 1
#include "stickman/StickMan.hpp"

class Player: public StickMan
{
  StickMan * target;

public:
  Player();
};
#endif
