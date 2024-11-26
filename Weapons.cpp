//---------------------------------------------------------------------------------------------------------------------
// Weapon.cpp
//
// This is the source file for the Weapon class.
//
// Group: 090
//
// Author: Sarah Pennauer, 01331166
//----------

#include "Weapons.hpp"

Weapon::Weapon(std::string weapon_abbrev, std::string name, AttackType attack_type, DamageType damage_type,
               DamagePattern damage_pattern, std::string damage_amount, int roll_amount, int dice_type)
{
  abbreviation_ = weapon_abbrev;
  name_ = name;
  attack_type_ = attack_type;
  damage_type_ = damage_type;
  damage_pattern_ = damage_pattern;
  damage_amount_ = damage_amount;
  roll_amount_ = roll_amount;
  dice_type_ = dice_type;
}

AttackType Weapon::getAttackType()
{
  return attack_type_;
}

DamageType Weapon::getDamageType()
{
  return damage_type_;
}

DamagePattern Weapon::getDamagePattern()
{
  return damage_pattern_;
}

int Weapon::getDiceType()
{
  return dice_type_;
}

int Weapon::getRollAmount()
{
  return roll_amount_;
}