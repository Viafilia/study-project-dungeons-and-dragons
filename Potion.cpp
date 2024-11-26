//---------------------------------------------------------------------------------------------------------------------
// Potion.cpp
//
// This is the source file for the Potion class, where all the methods are implemented.
//
// Group: 090
//
// Author: Sarah Pennauer, 01331166
//---------------------------------------------------------------------------------------------------------------------
//

#include "Potion.hpp"

HealthPotion::HealthPotion(std::string abbreviation, std::string name, std::string regenerated_health)
{
  abbreviation_ = abbreviation;
  name_ = name;
  regenerated_health_ = regenerated_health;
}

ResistancePotion::ResistancePotion(std::string abbreviation, std::string name, DamageType resistance_to)
{
  abbreviation_ = abbreviation;
  name_ = name;
  resistance_to_ = resistance_to;
}

int HealthPotion::countRegeneration()
{
  int health_to_add = 0;
  int amount = 0;
  int dice_type = 4;
  if (abbreviation_ == "NHEP")
  {
    amount = 2;
  }
  if (abbreviation_ == "GHEP")
  {
    amount = 4;
  }
  if (abbreviation_ == "SHEP")
  {
    amount = 8;
  }
  int sum = 0;
  for (int i = 0; i < amount; i++)
  {
    sum += Oop::Random::getInstance().getRandomNumber(dice_type);
  }
  std::cout << "[Dice Roll] " << amount << " d" << dice_type << " resulting in a total value of " << sum << ".\n\n";
  health_to_add = sum;
  return health_to_add;
}

void ResistancePotion::getResistance(std::string &damage_name, DamageType &damage_type)
{
  damage_type = resistance_to_;
  if (abbreviation_ == "FIRS")
  {
    damage_name = "Fire";
  }
  if (abbreviation_ == "CORS")
  {
    damage_name = "Cold";
  }
  if (abbreviation_ == "FORS")
  {
    damage_name = "Force";
  }
  if (abbreviation_ == "ACRS")
  {
    damage_name = "Acid";
  }
}