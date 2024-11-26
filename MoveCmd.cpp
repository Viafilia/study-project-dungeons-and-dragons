//---------------------------------------------------------------------------------------------------------------------
// MoveCmd.cpp
//
// This is the source file for the MoveCmd class, where all the methods are implemented.
//
// Group: 090
//
// Author: Julia Jesenko, 12312254
//---------------------------------------------------------------------------------------------------------------------
//

#include <iostream>
#include <string>
#include <vector>

#include "MoveCmd.hpp"
#include "Game.hpp"
#include "Exeption.hpp"

// copied from OOP A1 Tutors
///
bool MoveCmd::decimalStringToIntMove(const std::string &str, int &number)
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
// end

bool MoveCmd::execute()
{
  std::cout << "Sollte nie executed werden" << std::endl;
  return false;
};

MoveCmd::MoveCmd(std::vector<std::string> vectorized_input, int num_of_params, Game *game)
{
  type_ = CommandType::CMD_MOVE;
  num_of_params_ = num_of_params;
  game_ = game;
  if (num_of_params != 2)
  {
    throw Exception("E_INVALID_PARAM_COUNT", game_);
  }
  if (num_of_params_ > 0)
  {
    player_type_abbrev_ = vectorized_input.at(0);
  }
  if (num_of_params_ > 1)
  {
    std::string to_parse = vectorized_input.at(1);
    int pos = to_parse.find(",");
    if (pos == -1)
    {
      throw Exception("E_INVALID_PARAM", game_);
    }
    if (!decimalStringToIntMove(to_parse.substr(0, pos), position_.first))
    {
      throw Exception("E_INVALID_PARAM", game_);
    }
    if (!decimalStringToIntMove(to_parse.substr(pos + 1), position_.second))
    {
      throw Exception("E_INVALID_PARAM", game_);
    }
  }
}

int MoveCmd::executeMove()
{
  if (player_type_abbrev_ != "w" && player_type_abbrev_ != "b" && player_type_abbrev_ != "r")
  {
    throw Exception("E_INVALID_PARAM", game_);
  }
  int move_successfull = game_->makeMove(player_type_abbrev_, position_);
  if (move_successfull == false)
  {
    return 0;
  }
  if (move_successfull == 2) // it was a room change
  {
    return 5;
  }
  return 1;
}
