//----------------------------------------------------------------------------------------------------------------------
// MoveCmd.hpp
//
// The header file for the move command class, that is derived from the action command class
//
// Author: Julia Jesenko, 12312254
//----------------------------------------------------------------------------------------------------------------------
//
#ifndef MOVECOMMAND_HPP
#define MOVECOMMAND_HPP

#include "ActionCmd.hpp"

class MoveCmd : public ActionCmd
{
  private: 
    CommandType type_;
    std::pair<int,int> position_;

  public:
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The constructor initializes the members with the parameters' values and throws an error, if the user input is
    /// not valid.
    ///
    /// @param vectorized_input A vector, where every element is part of the user input.
    /// @param num_of_params The number of parameters, the user has entered.
    /// @param game A pointer to the game, where the command has to be executed
    //
    MoveCmd(std::vector<std::string> vectorized_input, int num_of_params, Game* game);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// We do not allow initializing one MoveCmd object to another one.
    //
    MoveCmd(const MoveCmd&) = delete;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Basic destructor for the MoveCmd
    //
    ~MoveCmd() = default;
    //---------------------------------------------------------------------------------------------------------------------
    ///
    /// A function that converts a string into an integer. Taken fron A1
    ///
    /// @param str THe string that should be converted to an integer.
    /// @param number The integer, where the number should be saved.
    /// @return true if the string could be converted, false if there was an error
    //
    // copied from OOP A1 Tutors
    ///
    bool decimalStringToIntMove(const std::string &str, int &number);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Function that executes the move command and returns different values, depending if it was sucessfully executed 
    /// or not.
    ///
    /// @param none
    ///
    /// @return 0 if it could not be executed, 1 if it was sucessfully executed, 5 if it was a room change
    //
    int executeMove();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Function if the virtual base class, that should in this case never be executed. If it is still the case, it 
    /// shows an error message.
    ///
    /// @param none
    ///
    /// @return always false
    //
    bool execute() override;
};

#endif
