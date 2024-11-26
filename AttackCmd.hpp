
//---------------------------------------------------------------------------------------------------------------------
//
// this is a header file for attack command, here attacks of players are executed
//
// Group: 090
//
// Author: Maryia Filipovich 12328063
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef ATTACKCOMMAND_HPP
#define ATTACKCOMMAND_HPP

#include "ActionCmd.hpp"

class AttackCmd : public ActionCmd
{
  private:
    std::pair<int, int> position_;

  public:
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a constructor of an Attack Command, that assignes its attributes
    /// and throws errors if input was invalid.
    ///
    /// @param vectorized_input user input in for of tokens
    /// @param num_of_params number of parameters given by user
    /// @param game pointer to current game
    ///
    /// @return -
    //
    AttackCmd(std::vector<std::string> vectorized_input, int num_of_params, Game *game);
    //------------------------------------------------------------------------------------------------------------------
    /// This function is the copy constructor which is explicitely deleted.
    ///
    /// @param AttackCmd&: reference to the Attack Command
    ///
    /// @return -
    //
    AttackCmd(const AttackCmd &) = delete;
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a virutal default destructor of an Attack Command.
    ///
    /// @param -
    ///
    /// @return -
    //
    ~AttackCmd() = default;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// execution of attack command, is used to make damage on characters on the field using equiped weapon
    ///
    ///
    /// @return correctness of execution
    //
    bool execute() override;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// function checks if there is no more alive players in the Room
    ///
    /// @return 1 if there is no players alive, 0 otherwise
    //
    bool allPlayersDead();
};

#endif
