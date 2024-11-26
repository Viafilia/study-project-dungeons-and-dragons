//---------------------------------------------------------------------------------------------------------------------
// LootCmd.cpp
//
// This is the source file for the LootCmd class, where all the methods are implemented.
//
// Group: 090
//
// Author: Sarah Pennauer, 01331166
//---------------------------------------------------------------------------------------------------------------------
//

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#include "DisplayCmd.hpp"
#include "LootCmd.hpp"
#include "Game.hpp"
#include "Exeption.hpp"

// copied from OOP A1 Tutors
///
bool LootCmd::decimalStringToInt_local(const std::string &str, int &number)
{
  size_t position = 0;
  try
  {
    number = std::stoul(str, &position, 10);
  }
  catch (std::exception &)
  {
    return false;
  }
  return position == str.length();
}
//

LootCmd::LootCmd(std::vector<std::string> vectorized_input, int num_of_params, Game *game)
{
  game_ = game;
  type_ = CommandType::CMD_LOOT;
  num_of_params_ = num_of_params;
  looting_player_ = nullptr;
  int num_of_params_ = num_of_params;
  game_ = game;
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
    std::string to_parse = vectorized_input.at(1);
    int pos = to_parse.find(",");
    if (pos == -1)
    {
      throw Exception("E_INVALID_PARAM", game_);
    }
    if (!decimalStringToInt_local(to_parse.substr(0, pos), position_.first))
    {
      throw Exception("E_INVALID_PARAM", game_);
    }
    if (!decimalStringToInt_local(to_parse.substr(pos + 1), position_.second))
    {
      throw Exception("E_INVALID_PARAM", game_);
    }
  }
}

bool LootCmd::execute()
{
  if (num_of_params_ != 2)
  {
    game_->writeStory("E_INVALID_PARAM_COUNT");
    return false;
  }

  if (!checkPlayerAbbrevValidity() || !checkPositionParamValidity())
  {
    return false;
  }

  Room *room = game_->getActiveRoom();
  std::vector<std::vector<Entity *>> &fields = room->getFields();

  Entity *entity = fields.at(position_.first - 1).at(position_.second - 1);

  if (entity != nullptr && entity->getAbbrev().compare("T") == 0)
  {
    TreasureChest *treasure_chest = dynamic_cast<TreasureChest *>(entity);
    if (!lootTreasureChest(treasure_chest))
    {
      game_->writeStory("N_LOOT_CHEST_LOCKED");
      return true; // COUNTS AS AN ACTION!
    }

    fields.at(position_.first - 1).at(position_.second - 1) = nullptr; // to replace deleted treasure chest
    delete treasure_chest;
    return true;
  }
  else if (entity != nullptr && entity->getAbbrev().compare("X") == 0)
  {
    DeathLocation *death_location = dynamic_cast<DeathLocation *>(entity);

    lootDeathLocation(death_location);                             // loot cannot fail, always true, so no check needed
    fields.at(position_.first - 1).at(position_.second - 1) = nullptr; // to replace deleted death location
    delete death_location;

    return true;
  }
  else
  {
    game_->writeStory("E_INVALID_POSITION");
  }
  return false;
}

bool LootCmd::checkPlayerAbbrevValidity()
{
  if (player_type_abbrev_.compare("w") != 0 && player_type_abbrev_.compare("b") != 0 && // input != w, r, b
      player_type_abbrev_.compare("r") != 0)
  {
    game_->writeStory("E_INVALID_PARAM");
    return false;
  }
  player_type_abbrev_[0] = std::toupper(player_type_abbrev_[0]);

  looting_player_ = nullptr;

  for (Player *player : game_->getPlayers()) // get the correct player from game vector
  {
    if (player_type_abbrev_.compare(player->getAbbreviation()) == 0)
    {
      looting_player_ = player;
    };
  }

  if (looting_player_ == nullptr || looting_player_->getHealth() == 0) // player is dead already
  {
    game_->writeStory("E_ENTITY_OR_ITEM_UNAVAILABLE");
    return false;
  }

  return true; // true if player abbrev was valid, is an actively chosen player type and is still alive
}

bool LootCmd::checkPositionParamValidity()
{
  Room *room = game_->getActiveRoom();

  if (position_.first > room->getHeight() || position_.second > room->getWidth() || // out of bounds check
      position_.first < 1 || position_.second < 1)
  {
    game_->writeStory("E_INVALID_POSITION");
    return false;
  }

  if (position_.first == (looting_player_->getPosition().first + 1) && // player position == target position
      position_.second == (looting_player_->getPosition().second + 1))
  {
    game_->writeStory("E_INVALID_POSITION");
    return false;
  }

  if (position_.first > (looting_player_->getPosition().first + 2) || // loot position is not adjacent to player
      position_.first < (looting_player_->getPosition().first) ||
      position_.second > (looting_player_->getPosition().second + 2) ||
      position_.second < (looting_player_->getPosition().second))
  {
    game_->writeStory("E_INVALID_POSITION");
    return false;
  }

  return true;
}

bool LootCmd::lootTreasureChest(TreasureChest *&treasure_chest)
{
  int min_value_to_roll = treasure_chest->getValueToUnlock() - looting_player_->getVitality();
  std::cout << "** To unlock this chest you need to roll at least " << min_value_to_roll;
  std::cout << " to reach the " << treasure_chest->getValueToUnlock() << " needed." << std::endl;

  int rolled_value = game_->diceRoll(1, 20);
  if (rolled_value < min_value_to_roll)
  {
    return false;
  }

  std::map<std::string, int> chest_loot_ = treasure_chest->getChestLoot()->getInventoryList();

  for (auto &[key, value] : chest_loot_)
  {
    if (value > 0)
    {
      looting_player_->getInventory()->changeInventoryItemAmount(key, value);
    }
  }

  printSuccessfulLoot(chest_loot_);

  return true;
}

bool LootCmd::lootDeathLocation(DeathLocation *&death_location)
{
  Inventory *death_location_loot = death_location->getDeathLocationLoot();
  std::map<std::string, int> death_loot_ = death_location_loot->getInventoryList();

  for (auto &[key, value] : death_loot_)
  {
    if (value > 0)
    {
      looting_player_->getInventory()->changeInventoryItemAmount(key, value);
    }
  }

  printSuccessfulLoot(death_loot_);

  return true;
}

void LootCmd::printSuccessfulLoot(std::map<std::string, int> &loot)
{
  game_->writeStory("N_LOOT_SUCCESSFUL");
  DisplayCmd *display_cmd = new DisplayCmd();
  std::vector<std::string> armor_list = looting_player_->getInventory()->getArmorList();
  std::vector<std::string> weapon_list = looting_player_->getInventory()->getWeaponList();
  std::vector<std::string> consumable_list = looting_player_->getInventory()->getConsumableList();

  display_cmd->printPlayerInventory("  Armor: ", loot, armor_list);
  display_cmd->printPlayerInventory("  Weapons: ", loot, weapon_list);
  display_cmd->printPlayerInventory("  Consumables: ", loot, consumable_list);

  delete display_cmd;
}
