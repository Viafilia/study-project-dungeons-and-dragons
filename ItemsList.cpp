//---------------------------------------------------------------------------------------------------------------------
// ItemsList.cpp
//
// This is the source file for the ItemsList class, where all the methods are implemented.
//
// Group: 090
//
// Author: Sarah Pennauer, 01331166
//---------------------------------------------------------------------------------------------------------------------
//

#include "ItemsList.hpp"

ItemsList::~ItemsList()
{
  {
    delete dagg;
    delete mace;
    delete warh;
    delete haxe;
    delete gaxe;
    delete rapi;
    delete sswd;
    delete lswd;
    delete gswd;
    delete sbow;
    delete lbow;
    delete lcrs;
    delete hcrs;

    delete qfir_wiz;
    delete qcld_wiz;
    delete qacd_wiz;
    delete qfrc_wiz;

    delete qfir;
    delete qcld;
    delete qacd;
    delete qfrc;

    delete nhep;
    delete ghep;
    delete shep;

    delete firs;
    delete cors;
    delete fors;
    delete acrs;

    delete arrw;
    delete bolt;

    delete larm;
    delete bplt;
    delete chml;
    delete parm;
  }
}

Weapon *ItemsList::getWeaponItemPtr(std::string item, bool is_wiz)
{
  for (Weapon *weapon : base_weapons_)
  {
    if (weapon->getAbbreviation() == item)
    {
      return weapon;
    }
  }
  if (!is_wiz)
  {
    for (Weapon *weapon : staff_weapons_)
    {
      if (weapon->getAbbreviation() == item)
      {
        return weapon;
      }
    }
  }
  else
  {
    for (Weapon *weapon : staff_weapons_wiz_)
    {
      if (weapon->getAbbreviation() == item)
      {
        return weapon;
      }
    }
  }

  return nullptr;
}

HealthPotion *ItemsList::getHealthPotionItemPtr(std::string item)
{

  for (HealthPotion *potion : health_potions_)
  {
    if (potion->getAbbreviation() == item)
    {
      return potion;
    }
  }
  return nullptr;
}

ResistancePotion *ItemsList::getResistPotionItemPtr(std::string item)
{

  for (ResistancePotion *potion : resist_potions_)
  {
    if (potion->getAbbreviation() == item)
    {
      return potion;
    }
  }
  return nullptr;
}

Ammunition *ItemsList::getAmmunitionItemPtr(std::string item)
{

  for (Ammunition *ammo : ammunition_items_)
  {
    if (ammo->getAbbreviation() == item)
    {
      return ammo;
    }
  }
  return nullptr;
}

Armor *ItemsList::getArmorItemPtr(std::string item)
{

  for (Armor *armor : armor_items_)
  {
    if (armor->getAbbreviation() == item)
    {
      return armor;
    }
  }
  return nullptr;
}

bool ItemsList::isConsumable(std::string item)
{
  for (Armor *armor : armor_items_)
  {
    if (armor->getAbbreviation() == item)
    {
      return true;
    }
  }
  for (ResistancePotion *potion : resist_potions_)
  {
    if (potion->getAbbreviation() == item)
    {
      return true;
    }
  }
  for (Weapon *weapon : base_weapons_)
  {
    if (weapon->getAbbreviation() == item)
    {
      return true;
    }
  }

  for (Weapon *weapon : staff_weapons_)
  {
    if (weapon->getAbbreviation() == item)
    {
      return true;
    }
  }
  for (HealthPotion *potion : health_potions_)
  {
    if (potion->getAbbreviation() == item)
    {
      return true;
    }
  }
  return false;
}