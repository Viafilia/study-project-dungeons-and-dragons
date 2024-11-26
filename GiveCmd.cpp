#include "GiveCmd.hpp"
#include "Exeption.hpp"
#include "Game.hpp"

GiveCmd::GiveCmd(std::vector<std::string> vectorized_input, int num_of_params, Game* game)
{

  type_ = CommandType::CMD_GIVE;
  game_ = game;
  item_list_ = game_->getItemsList();
  int num_of_params_ = num_of_params;
  if (num_of_params != 3)
  {
    throw Exception("E_INVALID_PARAM_COUNT", game_);
  }
  if (num_of_params_ > 0)
  {
    player1_type_abbrev_ = vectorized_input.at(0);
    if (player1_type_abbrev_ != "w" && player1_type_abbrev_ != "b" && player1_type_abbrev_ != "r")
    {
      throw Exception("E_INVALID_PARAM", game_);
    }
  }
  if (num_of_params_ > 1)
  {
    player2_type_abbrev_ = vectorized_input.at(1);
    if (player2_type_abbrev_ != "w" && player2_type_abbrev_ != "b" && player2_type_abbrev_ != "r")
    {
      throw Exception("E_INVALID_PARAM", game_);
    }
  }
  if (player1_type_abbrev_ == player2_type_abbrev_)
  {
    throw Exception("E_INVALID_PARAM", game_);
  }
  if (num_of_params_ > 2)
  {
    item_abbrev_ = vectorized_input.at(2);
  
    std::transform(item_abbrev_.begin(), item_abbrev_.end(), item_abbrev_.begin(), ::toupper);
    if (item_abbrev_ != "ARRW" && item_abbrev_ != "BOLT" && !item_list_->isConsumable(item_abbrev_))
    {
      throw Exception("E_INVALID_PARAM", game_);
    }
  }
}

bool GiveCmd::execute()
{
  Player* player1 = game_->getPlayer(player1_type_abbrev_);
  if(player1 == nullptr)
  {
    //we checked that int is one of the possible abbreviations in constuctor, that means the player is not in game
    throw Exception("E_ENTITY_OR_ITEM_UNAVAILABLE",game_);
  }
  if(player1->getAliveStatus() == false)
  {
    throw Exception("E_ENTITY_OR_ITEM_UNAVAILABLE",game_);
  }
  Player* player2 = game_->getPlayer(player2_type_abbrev_);
  if(player2 == nullptr)
  {
    //we checked that int is one of the possible abbreviations in constuctor, that means the player is not in game
    throw Exception("E_ENTITY_OR_ITEM_UNAVAILABLE",game_);
  }
  if(player2->getAliveStatus() == false)
  {
    throw Exception("E_ENTITY_OR_ITEM_UNAVAILABLE",game_);
  }
  if (!player1->changeItemAmount(item_abbrev_, -1))
  {
    throw Exception("E_ENTITY_OR_ITEM_UNAVAILABLE",game_);
  }
  player2->changeItemAmount(item_abbrev_, 1);
  std::cout << "Player " << player1->getName() << " gave Player " << player2->getName() << " " << item_abbrev_ << '\n';
  return 1;
}