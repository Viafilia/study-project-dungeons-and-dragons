//---------------------------------------------------------------------------------------------------------------------
// Inventory.cpp
//
// This is the source file for the Inventory class, where all the methods are implemented.
//
// Group: 090
//
// Author: Sarah Pennauer, 01331166
//---------------------------------------------------------------------------------------------------------------------
//

#include "Inventory.hpp"

Inventory::Inventory(CharacterType char_type_, InventoryType inventory_type_)
{
  inventory_list_ =
      {
          {"DAGG", 0}, {"MACE", 0}, {"WARH", 0}, {"HAXE", 0}, {"GAXE", 0}, {"RAPI", 0}, {"SSWD", 0}, {"LSWD", 0}, 
          {"GSWD", 0}, {"SBOW", 0}, {"LBOW", 0}, {"LCRS", 0}, {"HCRS", 0}, {"NHEP", 0}, {"GHEP", 0}, {"SHEP", 0}, 
          {"FIRS", 0}, {"CORS", 0}, {"FORS", 0}, {"ACRS", 0}, {"ARRW", 0}, {"BOLT", 0}, {"LARM", 0}, {"BPLT", 0}, 
          {"CHML", 0}, {"PARM", 0}};

  inventory_list_.insert({"QFIR", 0});
  inventory_list_.insert({"QCLD", 0});
  inventory_list_.insert({"QACD", 0});
  inventory_list_.insert({"QFRC", 0});

  initializeBaseInventory(char_type_, inventory_type_);
};

Inventory::Inventory(const Inventory &other)
{
  inventory_list_ = other.inventory_list_;
  armor_abbrevs_ = other.armor_abbrevs_;
  weapon_abbrevs_ = other.weapon_abbrevs_;
  consumable_abbrevs_ = other.consumable_abbrevs_;
}

std::map<std::string, int> Inventory::getInventoryList()
{
  return inventory_list_;
}

std::vector<std::string> Inventory::getArmorList()
{
  return armor_abbrevs_;
}

std::vector<std::string> Inventory::getWeaponList()
{
  return weapon_abbrevs_;
}

std::vector<std::string> Inventory::getConsumableList()
{
  return consumable_abbrevs_;
}

void Inventory::initializeBaseInventory(CharacterType character_type, InventoryType inventory_type)
{
  if (inventory_type == InventoryType::BASE)
  {
    switch (character_type)
    {
    case CharacterType::BARBARIAN:
      inventory_list_["HAXE"] = 2;
      break;
    case CharacterType::ROGUE:
      inventory_list_["DAGG"] = 2;
      inventory_list_["SBOW"] = 1;
      inventory_list_["ARRW"] = 20;
      break;
    case CharacterType::WIZARD:
      inventory_list_["QACD"] = 1;
      inventory_list_["DAGG"] = 1;
      break;
    case CharacterType::ZOMBIE:
      inventory_list_["DAGG"] = 1;
      break;
    case CharacterType::GOBLIN:
      inventory_list_["HAXE"] = 1;
      inventory_list_["SBOW"] = 1;
      inventory_list_["ARRW"] = -1; //-1 = infinite ammo
      break;
    case CharacterType::LICH: // always resistant to cold!
      inventory_list_["QFIR"] = 1;
      inventory_list_["QCLD"] = 1;
      inventory_list_["QACD"] = 1;
      inventory_list_["QFRC"] = 1;
      break;
    default:
      break;
    }
  }
  else if (inventory_type == InventoryType::LOOT)
  {
    switch (character_type)
    {
    case CharacterType::ZOMBIE:
      inventory_list_["DAGG"] = 1;
      break;
    case CharacterType::GOBLIN:
      inventory_list_["HAXE"] = 1;
      inventory_list_["SBOW"] = 1;
      inventory_list_["ARRW"] = 3;
      break;
    case CharacterType::LICH: // no loot
      break;
    default:
      break;
    }
  }

  armor_abbrevs_ = {"BPLT", "CHML", "LARM", "PARM"};
  weapon_abbrevs_ = {"DAGG", "GAXE", "GSWD", "HAXE", "HCRS", "LBOW", "LCRS", "LSWD", "MACE", "QACD", "QCLD", "QFIR",
                     "QFRC", "RAPI", "SBOW", "SSWD", "WARH"};
  consumable_abbrevs_ = {"ACRS", "ARRW", "BOLT", "CORS", "FIRS", "FORS", "GHEP", "NHEP", "SHEP"};
}

bool Inventory::changeInventoryItemAmount(std::string item, int amount_change)
{
  for (auto &[key, value] : inventory_list_)
  {
    if (key == item)
    {
      if (value + amount_change >= 0)
      {
        value += amount_change;
        return true;
      }
      else
      {
        return false;
      }
    }
  }
  return false;
}
