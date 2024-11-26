//---------------------------------------------------------------------------------------------------------------------
// Game.cpp
//
// This is the source file for the Game class, where all the methods are implemented.
//
// Group: 090
//
// Author: Maryia Filipovich 12328063, Sarah Pennauer 01331166, Julia Jesenko 12312254
//---------------------------------------------------------------------------------------------------------------------
//

#include "Game.hpp"
#include <set>
#include "Random.hpp"
#include <cctype>

Game::Game(Dungeon *dungeon, Story *story)
{
  dungeon_ = dungeon;
  story_ = story;
  items_list_ = new ItemsList();
  total_moves_ = 0;
  total_action_cmd_ = 0;
  completed_rooms_ = 0;
  phase_ = Phase::START;
  end_phase_ = EndPhase::QUIT;
}

void Game::startGame()
{
  CommandParser parser;
  phase_ = Phase::START;
  story_->printStory("N_INTRO");
  total_action_cmd_ = 0;
  std::cout << "How many players want to join the adventure? (1 to 3)\n";
  std::string input = "";
  bool eof = parser.getUserInput(input);
  int players_amount = 0;
  while (!players_amount && input != "quit" && eof != false)
  {
    bool valid = parser.decimalStringToInt(input, players_amount);
    if (!valid || !(players_amount <= 3 && players_amount > 0))
    {
      std::cout << "Please enter a number of players between 1 and 3.\n";
      if (!parser.getUserInput(input))
      {
        phase_ = Phase::END;
        return;
      }
      players_amount = 0;
    }
  }
  if (input == "quit" || eof == false)
  {
    phase_ = Phase::END;
    return;
  }
  players_amount_ = players_amount;
  total_moves_ = 0;
  std::map<std::string, bool> used; // shows if player type is used or not
  std::set<std::string> used_names;
  for (int i = 1; i <= players_amount_; i++)
  {
    std::cout << "\nPlayer " << i << " what do you wish to be called? (max length 10 characters)\n";
    std::string name;
    std::cout << "> ";
    if (!getline(std::cin, name)) // can't be quit or eof according to the README
    {
      phase_ = Phase::END;
      return;
    }
    while (name.size() > 10 || used_names.find(name) != used_names.end())
    {
      std::cout << "Please enter a unique name with not more than 10 characters.\n";
      std::cout << "> ";
      getline(std::cin, name); // can't be quit or eof, same reason as before
    }
    used_names.insert(name);
    std::cout << name << ", please choose a player type:\n"; // gehört da wirklich name oder nicht die ID (also i)
    std::cout << "  [W] Wizard     " << used["w"] << "/1\n";
    std::cout << "  [B] Barbarian  " << used["b"] << "/1\n";
    std::cout << "  [R] Rogue      " << used["r"] << "/1\n";
    std::string type;
    if (!parser.getUserInput(type))
    {
      for (auto p : players_)
      {
        if (p != nullptr)
        {
          delete p;
        }
      }
      phase_ = Phase::END;
      return;
    }
    while ((type != "r" && type != "b" && type != "w") || used[type])
    {
      if (type == "quit")
      {
        for (auto p : players_)
        {
          if (p != nullptr)
          {
            delete p;
          }
        }
        phase_ = Phase::END;
        return;
      }
      else if (type != "r" && type != "b" && type != "w")
        std::cout << "Please enter a letter representing your desired player type (W, B, or R).\n";
      else
        std::cout << "This player type is no longer available. Please choose a different player type.\n";
      if (!parser.getUserInput(type))
      {
        for (auto p : players_)
        {
          if (p != nullptr)
          {
            delete p;
          }
        }
        phase_ = Phase::END;
        return;
      }
    }
    used[type] = 1;

    // initializing a player
    Player *pll = new Player(name, type, i);
    if (type == "b")
    {
      Weapon *weapon = items_list_->getWeaponItemPtr("GAXE", 0); // giving player a weapon
      pll->equipWeapon(weapon);
    }
    if (type == "r")
    {
      Weapon *weapon = items_list_->getWeaponItemPtr("RAPI", 0); // giving player a weapon
      pll->equipWeapon(weapon);
      Armor *armor = items_list_->getArmorItemPtr("LARM");
      pll->equipArmor(armor);
    }
    if (type == "w")
    {
      Weapon *weapon = items_list_->getWeaponItemPtr("QFRC", 1); // giving player a weapon
      pll->equipWeapon(weapon);
    }
    players_.push_back(pll);
  }
  std::cout << "\n-- Players --------------------------------------\n";
  for (auto &player : players_)
  {
    player->printBanner();
  }
  std::cout << std::endl;
  dungeon_->changeActiveRoom(1);
  dungeon_->setPlayers(players_);
  dungeon_->placePlayers(1);

  do
  {
    if (!dungeon_->getActiveRoom()->allEnemiesDead())
    {
      dungeon_->printRoom();
    }
    startPlayerPhase();
    if (phase_ == Phase::END)
    {
      break;
    }
    startEnemyPhase();
  } while (phase_ != Phase::END);

  if (end_phase_ != EndPhase::QUIT)
  {
    startEndPhase(end_phase_);
  }
}

void Game::startEndPhase(EndPhase cause_of_end)
{
  switch (cause_of_end)
  {
  case EndPhase::DEFEAT:
    story_->printStory("N_DEFEAT");
    break;
  case EndPhase::FLIGHT:
    story_->printStory("N_FLIGHT");
    break;
  case EndPhase::COMPLETION:
    story_->printStory("N_COMPLETION");
    break;
  default:
    break;
  }

  gameScoring();
  saveEndToFile();
}

Game::~Game()
{
  delete items_list_;
}

Story *Game::getStory()
{
  return story_;
}

void Game::printMoves()
{
  std::cout << players_amount_ << std::endl;
}

void Game::gameScoring()
{

  completed_rooms_ = dungeon_->getCompletedRooms();
  std::cout << "-- Players --------------------------------------" << std::endl;

  for (Player *player : players_)
  {
    if (player->getHealth() > 0)
    {
      std::string pl_type_name = player->getTypeName();
      std::string pl_type_abbrev = player->getAbbreviation();
      std::string pl_name = player->getName();

      std::cout << "  " << pl_type_name << " [" << pl_type_abbrev << "] \"" << pl_name << "\" survived." << std::endl;
    }
  }

  for (Player *player : players_)
  {
    if (player->getHealth() < 1)
    {
      std::string pl_type_name = player->getTypeName();
      std::string pl_type_abbrev = player->getAbbreviation();
      std::string pl_name = player->getName();

      std::cout << "  " << pl_type_name << " [" << pl_type_abbrev << "] \"" << 
                           pl_name << "\", rest in peace." << std::endl;
    }
  }

  std::cout << std::endl
            << "-- Statistics -----------------------------------" << std::endl;
  std::cout << "  " << completed_rooms_ << " rooms completed" << std::endl;
  std::cout << "  " << total_action_cmd_ << " performed actions" << std::endl
            << std::endl;
}

void Game::saveEndToFile()
{
  story_->printStory("N_SCORING_FILE");
  std::string input = "";
  bool eof = false;
  bool writeable_file = false;

  do
  {
    std::cout << "> ";
    if (!std::getline(std::cin, input))
    {
      eof = true;
    }

    if (input == "quit" || eof == true)
    {
      return;
    }

    std::ofstream file(input, std::ios::trunc);
    if (file.is_open())
    {
      file.close();
      writeable_file = true;
    }
    else
    {
      story_->printStory("E_SCORING_FILE_NOT_WRITABLE");
    }
  } while (writeable_file == false);

  std::ofstream file(input, std::ios::trunc);
  file << "-- Players --------------------------------------" << std::endl;
  for (Player *player : players_)
  {
    if (player->getHealth() > 0)
    {
      std::string pl_type_name = player->getTypeName();
      std::string pl_type_abbrev = player->getAbbreviation();
      std::string pl_name = player->getName();

      file << "  " << pl_type_name << " [" << pl_type_abbrev << "] \"" << pl_name << "\" survived." << std::endl;
    }
  }

  for (Player *player : players_)
  {
    if (player->getHealth() < 1)
    {
      std::string pl_type_name = player->getTypeName();
      std::string pl_type_abbrev = player->getAbbreviation();
      std::string pl_name = player->getName();

      file << "  " << pl_type_name << " [" << pl_type_abbrev << "] \"" << pl_name << "\", rest in peace." << std::endl;
    }
  }

  file << std::endl
       << "-- Statistics -----------------------------------" << std::endl;
  file << "  " << completed_rooms_ << " rooms completed" << std::endl;
  file << "  " << total_action_cmd_ << " performed actions" << std::endl
       << std::endl;

  file.close();
}

void Game::setEndPhase(EndPhase end_phase)
  {
    end_phase_ = end_phase;
  }

  void Game::setPhase(Phase phase)
  {
    phase_ = phase;
  }

  void Game::completeRoom()
  {
    completed_rooms_ += 1;
  }

  ItemsList* Game::getItemsList()
  {
    return items_list_;
  }

  int Game::getNumberOfPlayers()
  {
    return players_amount_;
  }

  std::vector<Player*> Game::getPlayers()
  {
    return players_;
  }

void Game::startPlayerPhase()
{
  if (phase_ == Phase::END)
    return;
  phase_ = Phase::PLAYER;
  // dungeon_->printRoom();
  total_moves_ = 0;
  // int total_moves = 0;
  int invalid_cmd = 0;
  int *ptr = &invalid_cmd;

  if (this->getActiveRoom()->allEnemiesDead() && this->getActiveRoom()->getCompletion() == false)
  {
    this->completeRoom();
    dungeon_->updateCompletedRooms();
    this->getActiveRoom()->setCompletion();
    this->getActiveRoom()->unlockDoors();
    dungeon_->printRoom();
  }

  do
  {
    if (invalid_cmd == 0)
    {
      story_->printStory("N_PROMPT_MESSAGE");
    }
    CommandParser *command_parser = new CommandParser(this);

    int return_value = command_parser->parseCommand();
    if (return_value == 0) // it was quit or eof
    {
      phase_ = Phase::END;
    }
    else if (return_value == 2) // if it is invalid cmd -> not known or wrong amount param
    {
      invalid_cmd = 1;
    }
    else if (return_value == 1) // it was an action cmd
    {
      *ptr = 0;
      total_action_cmd_ = total_action_cmd_ + 1;
      if (phase_ != Phase::END)
        dungeon_->printRoom();
      total_moves_++;
    }
    else if (return_value == 5) // room change
    {
      total_action_cmd_ = total_action_cmd_ + 1;

      if (this->getActiveRoom()->allEnemiesDead() && this->getActiveRoom()->getCompletion() == false)
      {
        this->completeRoom();
        dungeon_->updateCompletedRooms();
        this->getActiveRoom()->setCompletion();
        this->getActiveRoom()->unlockDoors();
      }
      dungeon_->printRoom();
      startPlayerPhase();
    }
    else // it was a display cmd
    {
      invalid_cmd = 0;
    }
    delete command_parser;
  } while (phase_ != Phase::END && total_moves_ < players_amount_);
}

void Game::startEnemyPhase()
{
  phase_ = Phase::ENEMY;

  if (!(dungeon_->getActiveRoom()->allEnemiesDead()))
  {
    dungeon_->getActiveRoom()->enemyPhase();
    // dungeon_->printRoom();
  }
  if (dungeon_->getActiveRoom()->allPlayersDead())
  {
    phase_ = Phase::END;
    end_phase_ = EndPhase::DEFEAT;
  }
}

int Game::makeMove(std::string player, std::pair<int, int> coordiantes)
{
  int move = dungeon_->makeMove(player, coordiantes, story_);
  if (move == 1)
  {
    return true;
  }
  if (move == 2)
  {
    end_phase_ = EndPhase::FLIGHT;
    phase_ = Phase::END;
    return true;
  }
  if (move == 3) // Room change
  {
    return 2;
  }
  return false;
}

void Game::setQuit()
{
  phase_ = Phase::END;
}

int Game::diceRoll(int amount, int dice_type)
{
  int sum = 0;
  for (int i = 0; i < amount; i++)
  {
    sum += Oop::Random::getInstance().getRandomNumber(dice_type);
  }
  std::cout << "[Dice Roll] " << amount << " d" << dice_type << " resulting in a total value of " << sum << ".\n\n";
  return sum;
}

void Game::writeStory(std::string key)
{
  story_->printStory(key);
}

Room *Game::getActiveRoom()
{
  return dungeon_->getActiveRoom();
}

Player *Game::getPlayer(std::string id)
{
  for (char &cha : id)
  {
    cha = std::toupper(cha);
  }

  for (auto &player : players_)
  {
    if (player->getAbbreviation() == id)
    {
      return player;
    }
  }
  return nullptr;
}


std::vector<Enemy *> Game::getEnemies()
{
  return dungeon_->getActiveRoom()->getEnemies();
}

void Game::setOutput()
{
  dungeon_->setOutput();
}

void Game::setStoryOutput()
{
  dungeon_->setStoryOutput();
}
