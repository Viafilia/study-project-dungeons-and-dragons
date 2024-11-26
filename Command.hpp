//---------------------------------------------------------------------------------------------------------------------
// Command.hpp
//
// The header file contains the command class, which serves as a base class for action and display commands.
// The class stores the common attributes and the execute() method.
//
// Group: 090
//
// Author: Sarah Pennauer, 01331166
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include "ItemsList.hpp"


enum class CommandType
{
  CMD_QUIT, CMD_INVALID,
  CMD_HELP, CMD_STORY, CMD_MAP, CMD_POS, CMD_PLAYER, CMD_INVENTORY,
  CMD_MOVE, CMD_LOOT, CMD_USE, CMD_ATTACK, CMD_GIVE
};

// we declare game class here to avoid linking error, when command.hpp is included, because it has game pointer in it,
// but game isn't declared yet
class Game;
class Command
{
  protected: 
    Game* game_;
    int num_of_params_;
    ItemsList* item_list_ ;
  public: 
    //------------------------------------------------------------------------------------------------------------------
    /// This function is the default constructor for a Command object. 
    ///
    /// @param -
    ///
    /// @return -
    //
    Command() = default;
    //------------------------------------------------------------------------------------------------------------------
    /// This function is the copy constructor which is explicitely deleted. 
    ///
    /// @param Ammunition&: reference to the Command object 
    /// 
    /// @return -
    //   
    Command(const Command&) = delete;
    //------------------------------------------------------------------------------------------------------------------
    /// This function is the destructor of the command class. 
    ///
    /// @param -
    /// 
    /// @return -
    //   
    virtual ~Command(){};
    //------------------------------------------------------------------------------------------------------------------
    /// This function is the execute function of the command class which is purely virtual. 
    ///
    /// @param -
    /// 
    /// @return 1 if the execution was correct, 0 otherwise
    //   
    virtual bool execute() = 0;
};

#endif
