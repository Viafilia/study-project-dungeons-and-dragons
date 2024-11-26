//---------------------------------------------------------------------------------------------------------------------
// UseCmd.cpp
//
// This is the source file for the UseCmd class.
//
// Group: 090
//
// Author: Maryia Filipovich, 12328063
//---------------------------------------------------------------------------------------------------------------------
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "UseCmd.hpp"
#include "Player.hpp"
#include "Weapons.hpp"
#include "Exeption.hpp"
#include "Game.hpp"
#include "Exeption.hpp"

UseCmd::UseCmd(std::vector<std::string> vectorized_input, int num_of_params, Game* game)
{
  type_ = CommandType::CMD_USE;
  game_ = game;
  item_list_ = game_->getItemsList();
  int num_of_params_ = num_of_params;
  if (num_of_params != 2)
  {
    throw Exception("E_INVALID_PARAM_COUNT", game_);
  }
  if (num_of_params_ > 0)
  {
    player_type_abbrev_ = vectorized_input.at(0);
    if (player_type_abbrev_ != "w" && player_type_abbrev_ != "b" && player_type_abbrev_ != "r")
    {
      throw Exception("E_INVALID_PARAM", game_);
    }
  }
  if (num_of_params_ > 1)
  {
    item_abbrev_ = vectorized_input.at(1);
  
    std::transform(item_abbrev_.begin(), item_abbrev_.end(), item_abbrev_.begin(), ::toupper);
    if (item_abbrev_ == "ARRW" || item_abbrev_ == "BOLT")
    {
      throw Exception("E_INVALID_PARAM", game_);
    }
    else if (!item_list_->isConsumable(item_abbrev_))
    {
      throw Exception("E_INVALID_PARAM", game_);
    }
  }
}


bool UseCmd::execute()
{
  Player* player = game_->getPlayer(player_type_abbrev_);
  if(player == nullptr)
  {
    //we checked that int is one of the possible abbreviations in constuctor, that means the player is not in game
    throw Exception("E_ENTITY_OR_ITEM_UNAVAILABLE",game_);
  }
  if(player->getAliveStatus() == false)
  {
    throw Exception("E_ENTITY_OR_ITEM_UNAVAILABLE",game_);
  }
  //check if it is equiped item
  if (Armor* ar = player->getEquippedArmor())
  {
    if (ar->getAbbreviation() == item_abbrev_)
    {
      player->equipArmor(nullptr);
      return 1;
    }
  }
  if (Weapon* weapon = player->getWeapon())
  {
    if (weapon->getAbbreviation() == item_abbrev_)
    {
      player->equipWeapon(nullptr);
      return 1;
    }
  }
  if (!player->changeItemAmount(item_abbrev_, -1))
  {
    throw Exception("E_ENTITY_OR_ITEM_UNAVAILABLE",game_);
  }
  else
  {
    
    if (item_abbrev_ == "NHEP" || item_abbrev_ == "GHEP" || item_abbrev_ == "SHEP")
    {
      
      std::string potion_name = item_list_->getHealthPotionItemPtr(item_abbrev_)->getName();
      std::cout << player->getTypeName() << " [" << player->getAbbreviation() << "] \"" << player->getName() << "\" consumed \""
    << potion_name <<"\".\n";
    int health_to_add = item_list_->getHealthPotionItemPtr(item_abbrev_)->countRegeneration();
      health_to_add = player->addHealth(health_to_add);
      
      std::cout << player->getTypeName() << " [" << player->getAbbreviation() << "] \"" << player->getName() << "\" regenerates "
      << health_to_add <<" health.\n";
    }
    else if (item_abbrev_ == "FIRS" || item_abbrev_ == "CORS" || item_abbrev_ == "FORS" || item_abbrev_ == "ACRS")
    {
      DamageType damage_type;
      std::string resistance_name;
      item_list_->getResistPotionItemPtr(item_abbrev_)->getResistance(resistance_name, damage_type);
      std::string potion_name = item_list_->getResistPotionItemPtr(item_abbrev_)->getName();
      std::cout << player->getTypeName() << " [" << player->getAbbreviation() << "] \"" << player->getName() << "\" consumed \""
      << potion_name <<"\".\n";
      std::cout << player->getTypeName() << " [" << player->getAbbreviation() << "] \"" << player->getName() << "\" is now resistant to \""
      << resistance_name <<"\" until leaving the room.\n";
      player->setResistance(damage_type);
    }
    else if (item_abbrev_ == "LARM" || item_abbrev_ == "BPLT" || item_abbrev_ == "CHML" || item_abbrev_ == "PARM")
    {
      player->equipArmor(item_list_->getArmorItemPtr(item_abbrev_));
    }
    else if (Weapon* weapon = item_list_->getWeaponItemPtr(item_abbrev_, player->getAbbreviation() == "W"))
    {
      player->equipWeapon(weapon);
    }
    else
    {
      throw Exception("E_ENTITY_OR_ITEM_UNAVAILABLE",game_);
    }
  }
  return 1;
}