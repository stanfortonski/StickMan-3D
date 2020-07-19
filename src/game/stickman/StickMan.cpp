/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#include "StickMan.hpp"

bool StickMan::isAttackRange() const
{
  if (isAnimPlay("left_kick"))
    return isLeftKickRange();
  else if (isAnimPlay("right_kick"))
    return isRightKickRange();
  else if (isAnimPlay("left_punch"))
    return isLeftPunchRange();
  else if (isAnimPlay("right_punch"))
    return isRightPunchRange();
  return false;
}

bool StickMan::isWhileKicking() const
{
  return isAnimPlay("left_kick") || isAnimPlay("right_kick");
}

bool StickMan::isWhilePunching() const
{
  return isAnimPlay("left_punch") || isAnimPlay("right_punch");
}

bool StickMan::isWhileAttack() const
{
  return isWhileKicking() || isWhilePunching();
}

void StickMan::init()
{
  StickManModel::init();
  hp = MAX_HP;
  attackWithoutBlockCount = 0;
  perfectBlockCount = 0;
}

void StickMan::render(Program & program)
{
  glDisable(GL_BLEND);
  glDisable(GL_CULL_FACE);

  if (hasNoHP() && !isDead())
    dead();
  else update();

  ModelAnim::render(program);

  glEnable(GL_BLEND);
  glEnable(GL_CULL_FACE);
}

void StickMan::update()
{
  if (isAnimationEnd() && target != nullptr)
  {
    if (!target->hasNoHP())
    {
      if (isAnimPlay("left_punch"))
        target->getHurt(calcDamageAndPunch(5));
      else if (isAnimPlay("right_punch"))
        target->getHurt(calcDamageAndPunch(12));
      else if (isAnimPlay("left_kick"))
        target->getHurt(calcDamageAndKick(7.5));
      else if (isAnimPlay("right_kick"))
        target->getHurt(calcDamageAndKick(4));
    }
  }
  StickManModel::update();
}

float StickMan::getMultiplierFactor(const unsigned & blockCount)
{
  float multiplierFactor = DAMAGE_BLOCK_PROCENT - pow(blockCount * DEF_BONUS_FACTOR, 2) * 8;
  if (multiplierFactor < 0)
    multiplierFactor = 0.01;
  return multiplierFactor;
}

float StickMan::getHitBonus(const unsigned & attackCount)
{
  float hitBonus = HIT_BONUS_FACTOR * (pow(attackCount, 2)/2);
  if (hitBonus > 5)
    hitBonus = 5;
  return hitBonus;
}

float StickMan::getDistanceAttenuation()
{
  float dist = getDistanceBetween().x - RANGE_FACT*0.75;
  if (dist < 0)
    dist = 0;
  return DIST_ATTENUATION * pow(dist, 2);
}

float StickMan::calcDamageAndPunch(float damage)
{
  if (target != nullptr)
  {
    if (isAttackRange())
    {
      float distFactorAttenuation = getDistanceAttenuation(),
            multiplierFactor = 1, hitBonus = 0;
      if (target->isInPunchBlocking())
      {
        multiplierFactor = getMultiplierFactor(++target->perfectBlockCount);
        attackWithoutBlockCount = 0;
      }
      else
      {
        hitBonus = getHitBonus(++attackWithoutBlockCount);
        target->perfectBlockCount = 0;
        target->attackWithoutBlockCount = 0;
        target->punched();
      }

      damage = damage * multiplierFactor - distFactorAttenuation + hitBonus;
      if (damage < 0)
        damage = 0;
      return damage;
    }
  }
  return 0.0;
}

float StickMan::calcDamageAndKick(float damage)
{
  if (target != nullptr)
  {
    if (isAttackRange())
    {
      float distFactorAttenuation = getDistanceAttenuation(),
            multiplierFactor = 1, hitBonus = 0;
      if (target->isInKickBlocking())
      {
        multiplierFactor = getMultiplierFactor(++target->perfectBlockCount);
        attackWithoutBlockCount = 0;
      }
      else
      {
        hitBonus = getHitBonus(++attackWithoutBlockCount);
        target->perfectBlockCount = 0;
        target->attackWithoutBlockCount = 0;
        target->kicked();
      }

      damage = damage * multiplierFactor - distFactorAttenuation + hitBonus;
      if (damage < 0)
        damage = 0;
      return damage;
    }
  }
  return 0.0;
}

void StickMan::getHurt(float damage)
{
  hp -= damage;
  if (hp < 0)
    hp = 0;
}

glm::vec2 StickMan::getDistanceBetween() const
{
  if (target == nullptr)
    throw std::runtime_error("Error: getDistanceBetween() no target");

  float x = target->getPosition().x - getPosition().x;
  float y = target->getPosition().z - getPosition().z;
  return glm::vec2(abs(x), abs(y));
}

bool StickMan::checkDistanceForward() const
{
  return getPosition().x <= MAX_DISTANCE;
}

bool StickMan::checkDistanceBackward() const
{
  return getPosition().x >= -MAX_DISTANCE && getDistanceBetween().x <= MAX_DISTANCE_BETWEEN;
}

void StickMan::forwardWalk()
{
  if (getPosition().x <= MAX_DISTANCE - 0.5)
  {
    if (target != nullptr)
    {
      if (isRange() && target->checkDistanceForward())
      {
        static const float FACTOR = 0.35f;
        float mSpeed = target->getMoveSpeed();
        target->setMoveSpeed(mSpeed * FACTOR);
        target->translateBackward();
        target->setMoveSpeed(mSpeed);

        mSpeed = getMoveSpeed();
        setMoveSpeed(mSpeed * FACTOR);
        StickManModel::forwardWalk();
        setMoveSpeed(mSpeed);
      }
      else StickManModel::forwardWalk();
    }
    else StickManModel::forwardWalk();
  }
}

void StickMan::backwardWalk()
{
  if (checkDistanceBackward())
  {
    float mSpeed = target->getMoveSpeed();
    target->setMoveSpeed(mSpeed * 0.75);
    StickManModel::backwardWalk();
    target->setMoveSpeed(mSpeed);
  }
}

bool StickMan::leftPunch()
{
  static float DELAY = 0.05f;
  double time = glfwGetTime();
  if (time >= lastAttackTime)
  {
    StickManModel::leftPunch();
    lastAttackTime = time + DELAY;
    return true;
  }
  return false;
}

bool StickMan::rightPunch()
{
  static float DELAY = 0.58f;
  double time = glfwGetTime();
  if (time >= lastAttackTime)
  {
    StickManModel::rightPunch();
    lastAttackTime = time + DELAY;
    return true;
  }
  return false;
}

bool StickMan::leftKick()
{
  static float DELAY = 0.28f;
  double time = glfwGetTime();
  if (time >= lastAttackTime)
  {
    StickManModel::leftKick();
    lastAttackTime = time + DELAY;
    return true;
  }
  return false;
}

bool StickMan::rightKick()
{
  static float DELAY = 0.18f;
  double time = glfwGetTime();
  if (time >= lastAttackTime)
  {
    StickManModel::rightKick();
    lastAttackTime = time + DELAY;
    return true;
  }
  return false;
}

bool StickMan::kickDefense()
{
  static float DELAY = 0.11f;
  double time = glfwGetTime();
  if (time >= lastAttackTime)
  {
    StickManModel::kickDefense();
    lastAttackTime = time + DELAY;
    return true;
  }
  return false;
}

bool StickMan::punchDefense()
{
  static float DELAY = 0.10f;
  double time = glfwGetTime();
  if (time >= lastAttackTime)
  {
    StickManModel::punchDefense();
    lastAttackTime = time + DELAY;
    return true;
  }
  return false;
}
