//---------------------------------------------------------------------------------------------------------------------
// Dungeon.cpp
//
// This is the source file of the dungeon class, where all the methods are implemented.
//
// Group: 090
//
// Author: Julia Jesenko, 12312254
//---------------------------------------------------------------------------------------------------------------------
//
#include "Dungeon.hpp"
#include "Story.hpp"
#include <set>

Dungeon::Dungeon(char *file_name, Story *story)
{
  story_ = story;
  output_active_ = true;
  story_output_active_ = true;
  std::vector<Room *> room_template;
  completed_rooms_ = 0;
  std::string config = file_name;
  std::ifstream file{config};
  std::string line;
  getline(file, line);
  int room_amount = 0;
  while (std::getline(file, line))
  {
    Room *room = new Room(line);
    room_template.push_back(room);
    room_amount++;
  }
  rooms_ = room_template;
  active_room_ = rooms_.at(0);
  max_rooms_ = room_amount;
}

Dungeon::~Dungeon()
{
  for (auto &c : rooms_)
  {
    delete c;
  }
  for (auto &p : players_)
  {
    if (p != nullptr)
    {
      delete p;
    }
  }
}

void Dungeon::updateCompletedRooms()
{
  completed_rooms_ = 0;
  for (Room *room : rooms_)
  {
    if (room->getCompletion() == true)
    {
      completed_rooms_++;
    }
  }
}

int Dungeon::getCompletedRooms()
{
  completed_rooms_ = 0;
  for (Room *room : rooms_)
  {
    if (room->getCompletion() == true)
    {
      completed_rooms_++;
    }
  }

  return completed_rooms_;
}
void Dungeon::setPlayers(std::vector<Player *> players)
{
  players_ = players;
}

void Dungeon::placePlayers(int room_change)
{
  active_room_->placePlayers(players_, room_change);
}

void Dungeon::printRoom()
{
  if (!active_room_->notEntered())
  {
    if (story_output_active_)
      story_->printStory("N_ROOM_" + std::to_string(active_room_->getNumber()));
    active_room_->setEntered();
  }
  std::set<std::string> abbrev = active_room_->getEnemyTypes();
  for (auto en : abbrev)
  {
    if (printed_enemies_.find(en) == printed_enemies_.end())
    {
      if (story_output_active_)
        story_->printStory("N_ENEMY_" + en);
      printed_enemies_.insert(en);
    }
  }

  updateCompletedRooms();

  std::cout << "\n-- ROOM " << active_room_->getNumber() << " (" << completed_rooms_ << "/" << max_rooms_ << 
               " completed) --------------------\n\n";
  if (output_active_ == true)
  {
    std::cout << (*active_room_);
  }
  active_room_->printEnemyStats();
}

void Dungeon::changeActiveRoom(int room_num)
{
  active_room_ = rooms_.at(room_num - 1);
}

int Dungeon::makeMove(std::string player, std::pair<int, int> coordinates, Story *story)
{
  Player *active_player = nullptr;
  int target_row = coordinates.first;
  int target_col = coordinates.second;
  for (char &cha : player)
  {
    cha = std::toupper(cha);
  }
  for (auto c : players_)
  {
    if (player == c->getAbbreviation())
    {
      active_player = c;
    }
  }
  if (active_player == nullptr)
  {
    story->printStory("E_ENTITY_OR_ITEM_UNAVAILABLE");
    return false;
  }
  else if (active_player->getAliveStatus() == false)
  {
    story->printStory("E_ENTITY_OR_ITEM_UNAVAILABLE");
    return false;
  }
  if (!active_room_->checkIfExist(target_row, target_col))
  {
    story->printStory("E_INVALID_POSITION");
    return false;
  }
  int move = active_room_->moveExecute(active_player, target_row - 1, target_col - 1, story);
  if (move != -1 && move != -2 && move != 0)
  {
    int room_change = 0;
    int room_num = active_room_->getNumber();
    if (room_num < move)
    {
      room_change = 1;
    }
    else if (room_num > move)
    {
      room_change = -1;
    }
    changeActiveRoom(move);
    placePlayers(room_change);
    return 3;
  }
  if (move == 0)
  {
    return 2;
  }
  if (move == -2) // if move could not be executed
  {
    return 0;
  }
  return 1;
}

Room *Dungeon::getActiveRoom()
{
  return active_room_;
}

void Dungeon::setOutput()
{
  if (output_active_ == true)
  {
    output_active_ = false;
  }
  else if (output_active_ == false)
  {
    output_active_ = true;
    std::cout << (*active_room_);
  }
}

void Dungeon::setStoryOutput()
{
  story_output_active_ ^= 1;
}