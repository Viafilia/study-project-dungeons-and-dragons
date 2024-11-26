//---------------------------------------------------------------------------------------------------------------------
// DisplayCmd.cpp
//
// This is the source file for the DisplayCmd class, where all the methods are implemented.
//
// Group: 090
//
// Author: Maryia Filipovich 12328063, Sarah Pennauer 01331166, Julia Jesenko 12312254
//---------------------------------------------------------------------------------------------------------------------
//

#include <iostream>
#include <vector>
#include <string>
#include "Exeption.hpp"

#include "ItemsList.hpp"
#include "DisplayCmd.hpp"
#include "Game.hpp"

DisplayCmd::DisplayCmd(CommandType type, std::vector<std::string> vectorized_input, int num_of_params, Game* game)
{
  type_ = type;
  num_of_params_ = num_of_params;
  if (num_of_params > 0)
  {
    player_type_abbrev_ = vectorized_input.at(0);
  }
  game_ = game;
  item_list_ = game_->getItemsList();
}

bool DisplayCmd::execute()
{
  switch (type_)
  {
    case CommandType::CMD_HELP:
      return executeHelpCmd();
    case CommandType::CMD_STORY:
      return executeStoryCmd();
    case CommandType::CMD_MAP:
      return executeMapCmd();
    case CommandType::CMD_POS:
      return executePosCmd();
    case CommandType::CMD_PLAYER:
      return executePlayerCmd();
    case CommandType::CMD_INVENTORY:
      return executeInventoryCmd();
    default:
      break;
  }

  return false;
}

bool DisplayCmd::executeHelpCmd()
{
  if (num_of_params_ != 0)
  {
    throw Exception("E_INVALID_PARAM_COUNT", game_);
  }
  printHelp();
  return true;
}

void DisplayCmd::printHelp()
{
  std::cout << "-- Commands ----------------------------------------\n"
               "- help\n"
               "     Prints this help text.\n\n"
               "- quit\n"
               "    Terminates the game.\n\n"
               "- story\n"
               "    Activates or deactivates the stories of the rooms.\n\n"
               "- map\n"
               "    Activates or deactivates the map.\n\n"
               "- positions\n"
               "    Prints the current positions of the players and enemies.\n\n"
               "- player <PLAYER_TYPE_ABBREVIATION>\n"
               "    Prints player information of the specific player.\n"
               "    <PLAYER_TYPE_ABBREVIATION>: type of the player\n\n"
               "- inventory <PLAYER_TYPE_ABBREVIATION>\n"
               "    Prints the inventory of the specific player.\n"
               "    <PLAYER_TYPE_ABBREVIATION>: type of the player\n\n"
               "* move <PLAYER_TYPE_ABBREVIATION> <POSITION>\n"
               "    Lets the player move to an adjacent field.\n"
               "    <PLAYER_TYPE_ABBREVIATION>: type of the player\n"
               "    <POSITION>: field at position: <ROW>,<COLUMN>\n\n"
               "* loot <PLAYER_TYPE_ABBREVIATION> <POSITION>\n"
               "    Lets the player loot an adjacent chest.\n"
               "    <PLAYER_TYPE_ABBREVIATION>: type of the player\n"
               "    <POSITION>: field at position: <ROW>,<COLUMN>\n\n"
               "* use <PLAYER_TYPE_ABBREVIATION> <ITEM_ABBREVIATION>\n"
               "    Lets the player use a potion or equip armor or weapons.\n"
               "    <PLAYER_TYPE_ABBREVIATION>: type of the player\n"
               "    <ITEM_ABBREVIATION>: abbreviation of an item in the players inventory\n\n"
               "* attack <PLAYER_TYPE_ABBREVIATION> <POSITION>\n"
               "    Lets the player attack with the equipped weapon on the given position.\n"
               "    <PLAYER_TYPE_ABBREVIATION>: type of the player\n"
               "    <POSITION>: field at position: <ROW>,<COLUMN>\n\n"
               "-- Legend ------------------------------------------\n"
               "- display commands\n"
               "* action commands (count as actions)\n"
               "----------------------------------------------------\n";
}

bool DisplayCmd::executeStoryCmd()
{
  if (num_of_params_ != 0)
  {
    throw Exception("E_INVALID_PARAM_COUNT", game_);
  }
  game_->setStoryOutput();
  return true;
}

bool DisplayCmd::executeMapCmd()
{
  if(num_of_params_ != 0)
  {
    throw Exception("E_INVALID_PARAM_COUNT", game_);
  }
  game_->setOutput();
  return true;
}

bool DisplayCmd::executePosCmd()
{
  if(num_of_params_ != 0)
  {
    throw Exception("E_INVALID_PARAM_COUNT", game_);
  }
  std::vector<Player*> players = game_->getPlayers();
  for(auto& c : players)
  {
    if(c->getAliveStatus() == false)
    {}
    else
    {
      c->printPosition();
    }
  }
  std::vector<Enemy*> enemies = game_->getEnemies();
  for(auto& c : enemies)
  {
    if(c->getAliveStatus() == false)
    {}
    else
    {
      c->printPosition();
    }
  }
  return true;
}

bool DisplayCmd::executePlayerCmd()
{
  if(num_of_params_ != 1)
  {
    game_->writeStory("E_INVALID_PARAM_COUNT");
    return 0;
  }
  if(player_type_abbrev_.compare("w") != 0 && player_type_abbrev_.compare("b") != 0 && // input != w, r, b
    player_type_abbrev_.compare("r") != 0)
  {
    game_->writeStory("E_INVALID_PARAM");
    return false;
  }
  Player* player = game_->getPlayer(player_type_abbrev_);
  if (player == nullptr || player->getAliveStatus() == false)
  {
    game_->writeStory("E_ENTITY_OR_ITEM_UNAVAILABLE");
    return 0;
  }
  std::cout << player->getTypeName() << " [" << player->getAbbreviation() << "] \"" << player->getName() << 
               "\" on (" << player->getPosition().first + 1 << ',' << player->getPosition().second + 1 << ")\n";
  std::cout << "  Armor Value:    ";
  std::cout.width(5);
  std::cout << player->calcArmor() << '\n';
  std::cout << "  Current Health: ";
  std::cout.width(5);
  std::cout << player->getHealth() << '\n';
  std::cout << "  Max Health:     ";
  std::cout.width(5);
  std::cout << player->getMaxHealth() << '\n';
  std::cout << "  Strength:       ";
  std::cout.width(5);
  std::cout << player->getStrength() << '\n';
  std::cout << "  Vitality:       ";
  std::cout.width(5);
  std::cout << player->getVitality() << '\n';

  return true;
}

bool DisplayCmd::executeInventoryCmd()
{
  if(num_of_params_ != 1)
  {
    game_->writeStory("E_INVALID_PARAM_COUNT");
    return 0;
  }
  if(player_type_abbrev_.compare("w") != 0 && player_type_abbrev_.compare("b") != 0 && // input not abbrev w, r, b
    player_type_abbrev_.compare("r") != 0)
  {
    game_->writeStory("E_INVALID_PARAM");
    return false;
  }
  player_type_abbrev_[0] = std::toupper(player_type_abbrev_[0]);

  Player* inventory_player_ = nullptr;

  for(Player* player : game_->getPlayers()) // get the correct player from game vector
  {
    if(player_type_abbrev_.compare(player->getAbbreviation()) == 0)
    {
      inventory_player_ = player;
    };
  }

  if(inventory_player_ == nullptr || inventory_player_->getAliveStatus() == false) // player is non-existant or dead
  {
    game_->writeStory("E_ENTITY_OR_ITEM_UNAVAILABLE");
    return false;
  }

  Inventory* inventory = inventory_player_->getInventory();
  std::map<std::string, int> inventory_list = inventory->getInventoryList(); 

  std::cout << "Inventory \"" << inventory_player_->getName() << "\"" << std::endl;

  if(inventory_player_->getEquippedArmor() != nullptr)
  {
    std::cout << "  Equipped Armor: [" << inventory_player_->getEquippedArmor()->getAbbreviation() << "] " <<
                  inventory_player_->getEquippedArmor()->getName() << std::endl;
  }
  else
  {
    std::cout << "  Equipped Armor: [-] None" << std::endl;
  }

  if(inventory_player_->getWeapon() != nullptr)
  {
    std::cout << "  Equipped Weapon: [" << inventory_player_->getWeapon()->getAbbreviation() << "] " <<
                  inventory_player_->getWeapon()->getName() << std::endl;
  }
  else
  {
    std::cout << "  Equipped Weapon: [-] None" << std::endl;
  }

  std::vector<std::string> armor_list = inventory->getArmorList(); 
  std::vector<std::string> weapon_list = inventory->getWeaponList(); 
  std::vector<std::string> consumable_list = inventory->getConsumableList(); 

  printPlayerInventory("  Armor: ", inventory_list, armor_list);
  printPlayerInventory("  Weapons: ", inventory_list, weapon_list);
  printPlayerInventory("  Consumables: ", inventory_list, consumable_list);

  return true; 
}

void DisplayCmd::printPlayerInventory(std::string list_name, std::map<std::string, int>& inventory_list, 
                                      std::vector<std::string>& ref_list)
{
  if(checkListContents(ref_list, inventory_list))
  {
    ItemsList* item_list = new ItemsList(); 

    int comma_counter = 0;
    std::cout << list_name;

    for(std::string element : ref_list)
    {
      auto inventory_element = inventory_list.find(element);
      if(inventory_element != inventory_list.end() && inventory_element->second > 0) 
      {
        if(comma_counter != 0)
        {
          std::cout << ", ";
        }

        comma_counter++;
        std::string correct_abbrev = element;

        std::string name;

        Armor* armor = item_list->getArmorItemPtr(correct_abbrev);
        Weapon* weapon = item_list->getWeaponItemPtr(correct_abbrev, 0);
        HealthPotion* health_pot = item_list->getHealthPotionItemPtr(correct_abbrev);
        ResistancePotion* res_pot = item_list->getResistPotionItemPtr(correct_abbrev);
        Ammunition* ammo = item_list->getAmmunitionItemPtr(correct_abbrev);

        if(armor != nullptr)
        {
          name = (armor->getName());
        }
        else if(weapon != nullptr)
        {
          name = (weapon->getName());
        }        
        else if(health_pot != nullptr)
        {
          name = (health_pot->getName());
        }
        else if(res_pot != nullptr)
        {
          name = (res_pot->getName());
        }        
        else if(ammo != nullptr)
        {
          name = (ammo->getName());
        }

        std::cout << "[" << correct_abbrev << "] " << name << " (" << inventory_element->second << ")";
      }
    }
    delete item_list;
    std::cout << std::endl;
  }
}

bool DisplayCmd::checkListContents(std::vector<std::string>& ref_list, std::map<std::string, int>& inventory_list)
{
  for (std::string element : ref_list)
  {
    auto inventory_element = inventory_list.find(element);
    if(inventory_element != inventory_list.end() && inventory_element->second > 0) 
    {
      return true;
    }
  }

  return false;
}

