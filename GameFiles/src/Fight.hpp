/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#ifndef FIGHT_HPP
#define FIGHT_HPP 1
#include "Player.hpp"
#include "NPC.hpp"
#include "FightCamera.hpp"

class Fight
{
public:
  enum {WELCOME = 1, CHECK_RESULT = 2, WAIT_AFTER_LOSE = 3, WAIT_FOR_NEXT_ROUND = 4, FIGHT = 5, WIN_SHOW = 6, ENDED = 7};

private:
  int state;
  FightCamera & camera;
  unsigned totalRounds;
  unsigned actualRound;
  unsigned points1;
  unsigned points2;
  double waitTime;
  std::string message;
  double messageTime;

  StickMan & p1;
  StickMan & p2;

  void checkMessage();
  void init();
  void showLoseP1();
  void showLoseP2();
  void showWinP1();
  void showWinP2();

  void processWelcome();
  void checkRoute();
  void processCheckResult();
  void processWaitAfterLose();
  void processWaitForNextRound();
  void processFight();
  void processEndFight();

public:
  Fight(FightCamera & cam, StickMan & stickMan1, StickMan & stickMan2);

  void fight();

  const StickMan & getP1() const{return p1;}
  const StickMan & getP2() const{return p2;}
  unsigned getRoundsInTotal() const{return totalRounds;}
  unsigned getActualRound() const{return actualRound;}
  unsigned getP1sPoints() const{return points1;}
  unsigned getP2sPoints() const{return points2;}
  std::string getMessage() const{return message;}
  int getState() const{return state;}
};
#endif
