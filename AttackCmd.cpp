
//---------------------------------------------------------------------------------------------------------------------
// AttackCmd.cpp
//
// This is the source file for the AttackCmd class, where all the methods are implemented.
//
// Group: 090
//
// Author: Maryia Filipovich 12328063
//---------------------------------------------------------------------------------------------------------------------
//

#include <iostream>
#include <string>
#include <vector>
#include "Weapons.hpp"
#include "AttackCmd.hpp"
#include "Player.hpp"
#include "Room.hpp"
#include "Exeption.hpp"
#include "Game.hpp"
class Weapon;

//------------------------------------------------------------------------------------------------------------------
/// This function converts strint to an interer safely, is taken from A1 Utils
///
/// @param str: reference to the string to convert
/// @param number: reference to a numbers that will store the result
///
/// @return true if process was correct false otherwise
//
bool decimalStringToIntLocal(const std::string &str, int &number)
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

AttackCmd::AttackCmd(std::vector<std::string> vectorized_input, int num_of_params, Game *game)
{
  type_ = CommandType::CMD_ATTACK;
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
    if (!decimalStringToIntLocal(to_parse.substr(0, pos), position_.first))
    {
      throw Exception("E_INVALID_PARAM", game_);
    }
    if (!decimalStringToIntLocal(to_parse.substr(pos + 1), position_.second))
    {
      throw Exception("E_INVALID_PARAM", game_);
    }
  }
}

bool AttackCmd::execute()
{
  Player *player = game_->getPlayer(player_type_abbrev_);
  if (player == nullptr)
  {
    throw Exception("E_ENTITY_OR_ITEM_UNAVAILABLE", game_);
  }
  if (player->getAliveStatus() == false)
  {
    throw Exception("E_ENTITY_OR_ITEM_UNAVAILABLE", game_);
  }
  Weapon *weapon = player->getWeapon();
  Room *room = game_->getActiveRoom();
  if (weapon == nullptr)
  {
    throw Exception("E_ATTACK_NO_WEAPON_EQUIPPED", game_);
  }
  else
  {
    std::pair<int, int> player_position = player->getPosition();
    player_position.first++;
    player_position.second++;
    if (!room->checkPosition(position_) || (room->checkPosition(position_) &&
      weapon->getAttackType() == AttackType::MELEE && (abs(player_position.first - position_.first) > 1 || 
                                 abs(player_position.second - position_.second) > 1 || player_position == position_)))
    {
      throw Exception("E_INVALID_POSITION", game_);
    }

    if (weapon->getAbbreviation() == "LBOW" || weapon->getAbbreviation() == "SBOW")
    {
      if (!player->changeItemAmount("ARRW", -1))
      {
        throw Exception("E_ATTACK_NO_AMMUNITION", game_);
      }
    }
    if (weapon->getAbbreviation() == "LCRS" || weapon->getAbbreviation() == "HCRS")
    {
      if (!player->changeItemAmount("BOLT", -1))
      {
        throw Exception("E_ATTACK_NO_AMMUNITION", game_);
      }
    }

    std::cout << player->getTypeName() << " [" << player->getAbbreviation() << "] \"" << player->getName() << 
        "\" used \"" << weapon->getName() << "\" on (" << position_.first << "," << position_.second << ") affecting";

    std::vector<std::pair<int, int>> positions;

    if (weapon->getDamagePattern() == DamagePattern::HIT)
    {
      if (room->checkPosition(position_))
        positions.push_back(position_);
    }

    /////////////////////////////////////////////////////////////////////////

    if (weapon->getDamagePattern() == DamagePattern::THRUST)
    {
      if (room->checkPosition(position_))
        positions.push_back(position_);
      std::pair<int, int> position2 = std::make_pair(2 * (position_.first - player_position.first) +
                                                         player_position.first,
                                                     2 * (position_.second - player_position.second) +
                                                         player_position.second);
      if (room->checkPosition(position2))
        positions.push_back(position2);
    }

    ////////////////////////////////////////////////////////////////////////

    if (weapon->getDamagePattern() == DamagePattern::SLASH)
    {
      std::vector<std::pair<int, int>> coords{{0, 1}, {1, 1}, {1, 0}, {1, -1}, 
                                              {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}};
      if (room->checkPosition(position_))
        positions.push_back(position_);
      std::pair<int, int> position2 = player_position;
      for (unsigned int j = 0; j + 1 < coords.size(); j++)
      {
        if (coords[j] == std::make_pair(position_.first - player_position.first, position_.second -
                                                                                     player_position.second))
        {
          position2.first += coords[j + 1].first;
          position2.second += coords[j + 1].second;
        }
      }
      if (room->checkPosition(position2))
        positions.push_back(position2);
      position2 = player_position;
      for (int j = (int)coords.size() - 1; j > 0; j--)
      {
        if (coords[j] == std::make_pair(position_.first - player_position.first, position_.second -
                                                                                     player_position.second))
        {
          position2.first += coords[j - 1].first;
          position2.second += coords[j - 1].second;
        }
      }
      if (room->checkPosition(position2))
        positions.push_back(position2);
    }

    /////////////////////////////////////////////////////////////////

    if (weapon->getDamagePattern() == DamagePattern::LINE)
    {
      std::pair<int, int> delta = std::make_pair(position_.first - player_position.first, position_.second -
                                                                                              player_position.second);
      std::pair<int, int> position2 = position_;

      while (room->checkPosition(position2))
      {
        positions.push_back(position2);
        position2.first += delta.first;
        position2.second += delta.second;
      }
    }

    //////////////////////////////////////////////////////////////////////

    if (weapon->getDamagePattern() == DamagePattern::SHOT)
    {
      if (room->checkPosition(position_))
        positions.push_back(position_);
    }

    /////////////////////////////////////////////////////////////////////

    if (weapon->getDamagePattern() == DamagePattern::BURST)
    {
      if (room->checkPosition(position_))
        positions.push_back(position_);
      position_.second++;
      if (room->checkPosition(position_))
        positions.push_back(position_);
      position_.second -= 2;
      if (room->checkPosition(position_))
        positions.push_back(position_);
      position_.second++;
      position_.first++;
      if (room->checkPosition(position_))
        positions.push_back(position_);
      position_.first -= 2;
      if (room->checkPosition(position_))
        positions.push_back(position_);
      position_.first++;
    }

    std::sort(positions.begin(), positions.end());

    for (int i = 0; i < (int)positions.size(); i++)
    {
      auto p = positions[i];
      std::cout << " (" << p.first << ',' << p.second << ")";
      if (i != (int)positions.size() - 1)
        std::cout << ",";
      else
        std::cout << ".";
    }
    std::cout << '\n';

    int damage = game_->diceRoll(weapon->getRollAmount(), weapon->getDiceType());
    std::string abrev = weapon->getAbbreviation();
    if (abrev == "DAGG" || abrev == "RAPI" || abrev == "SSWD" || abrev == "SBOW" || abrev == "LBOW" ||
        abrev == "LCRS" || abrev == "HCRS")
    {
      damage += player->getVitality();
    }

    if (abrev == "MACE" || abrev == "WARH" || abrev == "HAXE" || abrev == "GAXE" || abrev == "LSWD" ||
        abrev == "GSWD" || (player_type_abbrev_ != "w" && (abrev == "QFIR" || abrev == "QCLD" || abrev == "QACD" || 
        abrev == "QFRC")))
    {
      damage += player->getStrength();
    }
    for (auto &p : positions)
    {
      room->makeDamage(p, weapon->getDamageType(), damage);
      if (room->allPlayersDead())
      {
        game_->setEndPhase(EndPhase::DEFEAT);
        game_->setPhase(Phase::END);
        return 1;
      }
      if (room->lichDead())
      {
        room->deleteEnemies();
        game_->setEndPhase(EndPhase::COMPLETION);
        game_->setPhase(Phase::END);
        return 1;
      }
      else if (room->allEnemiesDead())
      {
        game_->completeRoom();
        game_->getActiveRoom()->unlockDoors();
      }
    }
  }
  return 1;
}

bool AttackCmd::allPlayersDead()
{
  for (Player *player : game_->getPlayers())
  {
    if (player->getAliveStatus() == true)
    {
      return false;
    }
  }
  return true;
}