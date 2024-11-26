
//---------------------------------------------------------------------------------------------------------------------
//
// The header file contains the CommandParser class which manages user input and creates the corresponding commands 
// where necessary.
//
// Group: 090
//
// Author: Sarah Pennauer 01331166
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef COMMANDPARSER_HPP
#define COMMANDPARSER_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

#include "Game.hpp"
#include "Command.hpp"
#include "DisplayCmd.hpp"
#include "ActionCmd.hpp"
#include "MoveCmd.hpp"
#include "LootCmd.hpp"
#include "AttackCmd.hpp"
#include "UseCmd.hpp"
#include "GiveCmd.hpp"

class CommandParser
{
  private:
    std::map<std::string, CommandType> command_map_;
    Game* game_;

  public:
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a constructor for Command Parser which initialises the command_map_. 
    ///
    /// @param -
    ///
    /// @return -
    //
    CommandParser();
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a constructor for Command Parser which sets the Game* and initialises the command_map_. 
    ///
    /// @param -
    ///
    /// @return -
    //
    CommandParser(Game* game);
    //------------------------------------------------------------------------------------------------------------------
    /// This function sets the copy constructor of Command Parser to default. 
    ///
    /// @param -
    ///
    /// @return -
    //
    CommandParser(const CommandParser&) = default;
    //------------------------------------------------------------------------------------------------------------------
    /// This function sets the destructor of Command Parser to default. 
    ///
    /// @param -
    ///
    /// @return -
    //
    ~CommandParser() = default;

    //------------------------------------------------------------------------------------------------------------------
    /// This function handles all user-input related functions and also the creation of commands
    /// (first it gets the user input, then it vectorizes it, then it tries finding the cmd, then it creates the cmd)
    ///
    /// @param -
    /// @return 0: EOF or Quit
    /// @return 1: successfully executed action cmd
    /// @return 2: the command was not found or invalid amount param
    /// @return 3: successfully executed display cmd 
    int parseCommand();

    //------------------------------------------------------------------------------------------------------------------
    /// This function asks the user for input.
    ///
    /// @param input the user input
    /// @return false in case of EOF
    /// @return true on success
    //
    bool getUserInput(std::string& input);

    // adapted from A1: needs to be cited
    //------------------------------------------------------------------------------------------------------------------
    /// This function splits a string into tokens using a delimiter and stores the tokens in a vector.
    ///
    /// @param input the user input
    /// @return vectorized_string the split input string
    //
    std::vector<std::string> vectorizeInput(std::string& input);

    // copied from A1: needs to be cited
    //------------------------------------------------------------------------------------------------------------------
    /// This function removes trailing and leading whitespaces from a string.
    ///
    /// @param string - the sting to remove whitespaces from
    /// @return void
    //
    void removeWhitespacesAtEnds(std::string &string);

    // copied from A1: needs to be cited
    //------------------------------------------------------------------------------------------------------------------
    /// This function removes trailing whitespaces from a string.
    ///
    /// @param string - the sting to remove trailing whitespaces from
    /// @return void
    //
    void removeTrailingWhitespaces(std::string &string);

    // copied from A1: needs to be cited
    //------------------------------------------------------------------------------------------------------------------
    /// This function removes leading whitespaces from a string.
    ///
    /// @param string - the sting to remove leading whitespaces from
    /// @return void
    //
    void removeLeadingWhitespace(std::string &string);

    //------------------------------------------------------------------------------------------------------------------
    ///
    /// In this function the command the user entered (first part of the input) is compared to the command list.
    ///
    /// @param string the command part of the user input
    ///
    /// @return the corresponding command type (CMD_INVALID if cmd could not be found in list)
    //
    CommandType findCommand(std::string &string);

    //------------------------------------------------------------------------------------------------------------------
    ///
    /// In this function a command element corresponding to the user input is created and the corresponding execute 
    /// function is called.
    ///
    /// @param command the type of command
    /// @param vectorized_input the command parameters (user input without the cmd part)
    ///
    /// @return true on success
    /// @return false in case of bad_alloc or invalid command (parameters)
    //
    int createCommand(CommandType command, std::vector<std::string> vectorized_input, Game* game);

    //------------------------------------------------------------------------------------------------------------------
    ///
    /// this function safely converts a string to an integer (from a1)
    ///
    /// @param str string to convert
    /// @param number resulting integer
    ///
    /// @return true on success
    /// @return false in case string can't be converted
    //
    bool decimalStringToInt(const std::string& str, int& number);
    //------------------------------------------------------------------------------------------------------------------
    /// 
    /// this function changes all letters(if present) in string to lower case
    ///
    /// @param str string to transform
    //
    void toLower(std::string& str);
};

  #endif
