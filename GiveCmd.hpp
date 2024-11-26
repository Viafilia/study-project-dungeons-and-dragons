#ifndef GIVECMD_HPP
#define GIVECMD_HPP

#include "ActionCmd.hpp"

class GiveCmd : public ActionCmd
{
  private: 
    CommandType type_;
    std::string player1_type_abbrev_;
    std::string player2_type_abbrev_;
    std::string item_abbrev_;
  public:
    GiveCmd(std::vector<std::string> vectorized_input, int num_of_params, Game* game);
    GiveCmd(GiveCmd&) = delete;
    ~GiveCmd() = default;
    bool execute() override;
};

#endif