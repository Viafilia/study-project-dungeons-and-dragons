//---------------------------------------------------------------------------------------------------------------------
// CommandParser.cpp
//
// This is the source file for the CommandParser class, where all the methods are implemented.
//
// Group: 090
//
// Author: Sarah Pennauer 01331166
//---------------------------------------------------------------------------------------------------------------------
//

#include "CommandParser.hpp"
#include <memory>
#include "Exeption.hpp"

CommandParser::CommandParser()
{
  command_map_ = {{"quit", CommandType::CMD_QUIT},
    {"help", CommandType::CMD_HELP},
    {"story", CommandType::CMD_STORY},
    {"map", CommandType::CMD_MAP},
    {"positions", CommandType::CMD_POS},
    {"player", CommandType::CMD_PLAYER},
    {"inventory", CommandType::CMD_INVENTORY},
    {"move", CommandType::CMD_MOVE},
    {"loot", CommandType::CMD_LOOT},
    {"use", CommandType::CMD_USE},
    {"attack", CommandType::CMD_ATTACK}};
}

CommandParser::CommandParser(Game *game)
{
  command_map_ = {{"quit", CommandType::CMD_QUIT},
    {"help", CommandType::CMD_HELP},
    {"story", CommandType::CMD_STORY},
    {"map", CommandType::CMD_MAP},
    {"positions", CommandType::CMD_POS},
    {"player", CommandType::CMD_PLAYER},
    {"inventory", CommandType::CMD_INVENTORY},
    {"move", CommandType::CMD_MOVE},
    {"loot", CommandType::CMD_LOOT},
    {"use", CommandType::CMD_USE},
    {"give", CommandType::CMD_GIVE},
    {"attack", CommandType::CMD_ATTACK}};

  game_ = game;
}

int CommandParser::parseCommand()
{
  std::string input;
  if (!getUserInput(input)) // handle EOF
  {
    return 0;
  }

  std::vector<std::string> vectorized_input = vectorizeInput(input);
  CommandType command = findCommand(vectorized_input.at(0));
  if (command == CommandType::CMD_INVALID)
  {
    game_->writeStory("E_UNKNOWN_COMMAND");
    return 2;
  }
  else if (command == CommandType::CMD_QUIT && (int)vectorized_input.size() == 1)
  {
    return 0;
  }
  vectorized_input.erase(vectorized_input.begin()); // to delete the cmd-part

  int return_value = createCommand(command, vectorized_input, game_);
  if (return_value == 0)
  {
    return 2;
  }
  else if (return_value == 5)
  {
    return 5;
  }
  if (command == CommandType::CMD_MAP || command == CommandType::CMD_POS || command == CommandType::CMD_STORY ||
      command == CommandType::CMD_HELP || command == CommandType::CMD_PLAYER || command == CommandType::CMD_INVENTORY)
  {
    return 3;
  }
  return 1;
}

bool CommandParser::getUserInput(std::string &input)
{
  std::cout << "> ";
  if (!std::getline(std::cin, input))
  {
    return false;
  }
  removeWhitespacesAtEnds(input);
  toLower(input);
  if (input.empty())
  {
    input = " ";
  }
  return true;
}

std::vector<std::string> CommandParser::vectorizeInput(std::string &input)
{
  std::vector<std::string> vectorised_string;

  size_t position = 0;
  size_t position2;
  std::string split_word;
  while ((position2 = input.find(' ', position)) != std::string::npos)
  {
    split_word = input.substr(position, position2 - position);
    position = position2 + 1;
    removeWhitespacesAtEnds(split_word);
    if (!split_word.empty())
    {
      vectorised_string.push_back(split_word);
    }
  }
  vectorised_string.push_back(input.substr(position));
  return vectorised_string;
}

// copied from OOP A1 Tutors
///
bool CommandParser::decimalStringToInt(const std::string &str, int &number)
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

// copied from OOP A1 Tutors
///
void CommandParser::removeWhitespacesAtEnds(std::string &string)
{
  removeLeadingWhitespace(string);
  removeTrailingWhitespaces(string);
}
// end

// copied from OOP A1 Tutors
///
void CommandParser::removeTrailingWhitespaces(std::string &string)
{
  size_t end = string.find_last_not_of(' ');
  string = end == std::string::npos ? "" : string.substr(0, end + 1);
}
// end

// copied from OOP A1 Tutors
///
void CommandParser::removeLeadingWhitespace(std::string &string)
{
  auto start = string.find_first_not_of(' ');
  string = start == std::string::npos ? "" : string.substr(start);
}
// end

CommandType CommandParser::findCommand(std::string &string)
{
  std::map<std::string, CommandType>::iterator i = command_map_.find(string);
  if (i != command_map_.end())
  {
    return i->second;
  }
  if (string == "^D")
  {
    return CommandType::CMD_QUIT;
  }
  return CommandType::CMD_INVALID;
}

int CommandParser::createCommand(CommandType command, std::vector<std::string> vectorized_input, Game *game)
{
  std::size_t num_of_params = 0;
  int return_value = false;
  if (!vectorized_input.empty())
  {
    num_of_params = vectorized_input.size();
  }

  try
  {
    switch (command)
    {
    case CommandType::CMD_QUIT:
    {
      if (num_of_params != 0)
      {
        throw Exception("E_INVALID_PARAM_COUNT", game_);
      }
      else
      {
        game->setQuit();
      }
      break;
    }
    case CommandType::CMD_HELP:
    case CommandType::CMD_STORY:
    case CommandType::CMD_MAP:
    case CommandType::CMD_POS:
    case CommandType::CMD_PLAYER:
    case CommandType::CMD_INVENTORY:
    {
      std::unique_ptr<DisplayCmd> new_display_cmd = std::make_unique<DisplayCmd>(command, vectorized_input, 
                                                                                 num_of_params, game);
      return_value = new_display_cmd->execute();
      break;
    }
    case CommandType::CMD_MOVE:
    {
      std::unique_ptr<MoveCmd> new_move_cmd = std::make_unique<MoveCmd>(vectorized_input, num_of_params, game);
      return_value = new_move_cmd->executeMove();
      break;
    }
    case CommandType::CMD_GIVE:
    {
      std::unique_ptr<GiveCmd> new_give_cmd = std::make_unique<GiveCmd>(vectorized_input, num_of_params, game);
      return_value = new_give_cmd->execute();
      break;
    }
    case CommandType::CMD_LOOT:
    {
      std::unique_ptr<LootCmd> new_loot_cmd = std::make_unique<LootCmd>(vectorized_input, num_of_params, game);
      return_value = new_loot_cmd->execute();
      break;
    }
    case CommandType::CMD_USE:
    {
      std::unique_ptr<UseCmd> new_use_cmd = std::make_unique<UseCmd>(vectorized_input, num_of_params, game);
      return_value = new_use_cmd->execute();
      break;
    }
    case CommandType::CMD_ATTACK:
    {
      std::unique_ptr<AttackCmd> new_attack_cmd = std::make_unique<AttackCmd>(vectorized_input, num_of_params, game);
      return_value = new_attack_cmd->execute();
      break;
    }
    default:
      break;
    }
  }
  catch (const std::exception &e)
  {
    e.what();
    return 0;
  }
  return return_value;
}

void CommandParser::toLower(std::string &str)
{
  for (unsigned int i = 0; i < str.size(); i++)
  {
    if (str[i] >= 'A' && str[i] <= 'Z')
    {
      str[i] += 'a' - 'A';
    }
  }
}
