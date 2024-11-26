
//---------------------------------------------------------------------------------------------------------------------
// Character.cpp
//
// This is the source file for the Character class, where all the methods are implemented.
//
// Group: 090
//
// Author: Maryia Filipovich 12328063, Julia Jesenko 12312254
//---------------------------------------------------------------------------------------------------------------------
//

#include "Character.hpp"

void Character::getDamage(DamageType type, int damage)
{
  std::string how = std::to_string(damage) + " * ";
  if (resistance_ == type)
  {
    damage /= 2;
    how += "50 % - ";
  }
  else
  {
    how += "100 % - ";
  }
  how += std::to_string(calcArmor());
  damage -= calcArmor();
  damage = std::max(damage, 0);
  damage = std::min(damage, health_);
  health_ -= damage;
  std::cout << getName() << " loses " << damage << " health (" << how << ").\n";
  if (health_ <= 0)
  {
    std::cout << getName() << " was defeated.\n";
    die();
  }
}

int Character::getVitality()
{
  return vitality_;
}

int Character::getStrength()
{
  return strength_;
}