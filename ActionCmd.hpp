
//---------------------------------------------------------------------------------------------------------------------
//
// This is a header file for the action command class, which is a parent class for all action commands
//
// Group: 090
//
// Author: Sarah Pennauer, 01331166
//---------------------------------------------------------------------------------------------------------------------
//
#ifndef ACTIONCOMMAND_HPP
#define ACTIONCOMMAND_HPP

#include <string>

#include "Command.hpp"

class ActionCmd : public Command
{
  protected:
    CommandType type_;
    std::string player_type_abbrev_;

  public:
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a default constructor for an Action Command.
    ///
    /// @param -
    ///
    /// @return -
    //
    ActionCmd() = default;
    //------------------------------------------------------------------------------------------------------------------
    /// This function is the copy constructor which is explicitely deleted. 
    ///
    /// @param ActionCmd&: reference to the Action Command 
    /// 
    /// @return -
    //   
    ActionCmd(const ActionCmd&) = delete;
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a virutal default destructor of an Action Command.
    ///
    /// @param -
    ///
    /// @return -
    //
    virtual ~ActionCmd() = default;

    //------------------------------------------------------------------------------------------------------------------
    /// This function is a purely virtual execute function to be overwritten by the specific commands.
    ///
    /// @param -
    ///
    /// @return -
    //
    virtual bool execute() override = 0;
};

#endif
