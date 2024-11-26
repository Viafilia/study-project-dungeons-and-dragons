//---------------------------------------------------------------------------------------------------------------------
// UseCmd.hpp
//
// This class is user to proceed Use Command, that user can enter, depending on what item user wants to use.
//
// Group: 090
//
// Author: Maryia Filipovich, 12328063
//---------------------------------------------------------------------------------------------------------------------
//
#ifndef USECOMMAND_HPP
#define USECOMMAND_HPP

#include "ActionCmd.hpp"

class UseCmd : public ActionCmd
{
  private: 
    CommandType type_;
    std::string player_type_abbrev_;
    std::string item_abbrev_;

  public: 
    //------------------------------------------------------------------------------------------------------------------
    /// This function is the constructor of UseCmd class, that sets values to its attributes and throws errors in case
    /// of invalid input data
    ///
    /// @param vectorized_input user input in for of tokens
    /// @param num_of_params number of parameters given by user
    /// @param game pointer to current game
    ///
    /// @return -
    //
    UseCmd(std::vector<std::string> vectorized_input, int num_of_params, Game* game);
    //------------------------------------------------------------------------------------------------------------------
    /// This function is the copy constructor which is explicitely deleted. 
    ///
    /// @param UseCmd&: reference to the Use Command 
    /// 
    /// @return -
    //   
    UseCmd(const UseCmd&) = delete;
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a default destructor
    ///
    /// @param -
    /// 
    /// @return -
    //   
    ~UseCmd() = default;
    //------------------------------------------------------------------------------------------------------------------
    /// This function executes Use Command that is inputed by a user, it means (de)equipes weapon/armor and 
    /// sets effects of poitions
    ///
    /// @param -
    /// 
    /// @return 1 if the process was correct, 0 otherwise
    //   
    bool execute() override;
};

#endif
