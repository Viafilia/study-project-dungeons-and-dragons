//----------------------------------------------------------------------------------------------------------------------
// main.cpp
//
// This is the source file, where the dungeon, story and game class object gets created. The commandline arguments
// get checked and verified and if there is an error the programm exits with the right exit code
//
// Group: 090
//
// Author: Maryia Filipovich 12328063, Sarah Pennauer 01331166, Julia Jesenko 12312254
//----------------------------------------------------------------------------------------------------------------------
//
#include <iostream>
#include <string>
#include "CommandParser.hpp"
#include "Story.hpp"
#include "Dungeon.hpp"

#include "Game.hpp"

//----------------------------------------------------------------------------------------------------------------------
/// This function checks if the dungeon config starts with the right magic number.
///
/// @param file_name the name of the dungeon config file
///
/// @return true if the dungeon file is valid
/// @return false if the dungeon file was not valid
//
int validConfig(char* file_name)
{
  std::ifstream file(file_name);
  if (!file.is_open())
  {
    return false;
  }
  std::string magic_word;
  getline(file,magic_word);
  if (magic_word == "DUNGEON")
  {
    return true;
  }
  return false;
}

//----------------------------------------------------------------------------------------------------------------------
/// This function checks if the story config starts with the right magic number.
///
/// @param file_name the name of the story config file
///
/// @return true if the story file is valid
/// @return false if the story file was not valid
//
int validConfigStory(char* file_name)
{
  std::ifstream file(file_name);
  if (!file.is_open())
  {
    return false;
  }
  std::string magic_word;
  getline(file,magic_word);
  if (magic_word == "STORY")
  {
    return true;
  }
  return false;
}

//----------------------------------------------------------------------------------------------------------------------
/// The main function that is responsible for coordinating the other functions in this file and for creating a story,
/// dungeon and game object. If there is an error, the programm exits with the right exit code.
///
/// @param argc the amount of commandline arguments
/// @param argv the commandline argument vector
///
/// @return 0 if the game ended successfully (or via command)
/// @return 1 if the memory could not be allocated
/// @return 2 if the number of commandline arguments is invalid
/// @return 3 if the dungeon or story config was invalid
//
int main(int argc, char** argv)
{
  if (argc != 3)
  {
    std::cout << "Error: Wrong number of parameters!\n";
    return 2;
  }
  char* file_name = argv[1];
  char* story_file = argv[2];
  if (!validConfig(argv[1]))
  {
    std::cout << "Error: Invalid file (" << file_name << ")!\n";
    return 3;
  }
  else if (!validConfigStory(argv[2]))
  {
    std::cout << "Error: Invalid file (" << story_file << ")!\n";
    return 3;
  }
  Story story(argv[2]);
  
  try
  {
    Dungeon dungeon(argv[1], &story);
    Game game(&dungeon, &story);

    game.startGame();
  }
  catch (const std::bad_alloc& e)
  {
    std::cout << "Error: Not enough memory!\n";
    return 1;
  }

  return 0;
}