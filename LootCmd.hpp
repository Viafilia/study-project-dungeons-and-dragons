//---------------------------------------------------------------------------------------------------------------------
// LootCmd.hpp
//
// The header file contains the LootCmd class which is derived from ActionCmd and serves for managing loot commands.
//
// Group: 090
//
// Author: Sarah Pennauer, 01331166
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef LOOTCOMMAND_HPP
#define LOOTCOMMAND_HPP

#include "ActionCmd.hpp"
#include "CommandParser.hpp"
#include "Player.hpp"
#include "Room.hpp"
#include "DeathLocation.hpp"
#include "TreasureChest.hpp"

class LootCmd : public ActionCmd
{
  private: 
    CommandType type_;
    std::pair <int, int> position_;
    Player* looting_player_;

  public: 
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a constructor for a Loot Command. 
    ///
    /// @param vectorized_input: the user input minus the cmd part split in strings
    /// @param num_of_params: number of params (= number of strings in the vectorized_input)
    /// @param game: pointer to the game object
    ///
    /// @return -
    //
    LootCmd(std::vector<std::string> vectorized_input, int num_of_params, Game* game);
    //------------------------------------------------------------------------------------------------------------------
    /// This function is the copy constructor which gets deleted explicitely. 
    ///
    /// @param LootCmd&: reference to the LootCmd object 
    /// 
    /// @return -
    //   
    LootCmd(const LootCmd&) = delete;
    //------------------------------------------------------------------------------------------------------------------
    /// This function is the destructor which is set to default. 
    ///
    /// @param -
    /// 
    /// @return -
    //   
    ~LootCmd() = default;

    //------------------------------------------------------------------------------------------------------------------
    /// This function is the execute function for the loot command.
    /// In it, the command validity is checked and then the looting is executed.
    ///
    /// @param -
    ///
    /// @return true if the command is valid, regardless of if the dice roll value was enough for actually looting
    /// @return false if the command was somehow not valid
    //
    bool execute() override;
    //------------------------------------------------------------------------------------------------------------------
    /// This function checks if the player abbrev parameter is valid and the player is available.
    ///
    /// @param -
    ///
    /// @return true if the player type is valid and the player with that player type is alive
    /// @return false if the player is invalid
    //
    bool checkPlayerAbbrevValidity(); 
    //------------------------------------------------------------------------------------------------------------------
    /// This function checks if the position parameter is valid: out of bounds, same pos as player, adjacency
    ///
    /// @param -
    ///
    /// @return true if the position is valid and adjacent to the player
    /// @return false if the position is invalid
    //
    bool checkPositionParamValidity();
    //------------------------------------------------------------------------------------------------------------------
    /// This function lets the player roll a dice for looting a treasure chest and depending on the outcome moves
    /// the treasure loot into the player's inventory.
    ///
    /// @param -
    ///
    /// @return true if treasure chest loot was successful
    /// @return false if treasure chest loot was not successful
    //
    bool lootTreasureChest(TreasureChest* &treasure_chest);
    //------------------------------------------------------------------------------------------------------------------
    /// This function is for looting a corpse = moving the loot into the player's inventory.
    ///
    /// @param -
    ///
    /// @return true if loot was successful
    /// @return false if loot was unsuccessful (not active atm, for future implementation maybe)
    //
    bool lootDeathLocation(DeathLocation* &death_location);
    //------------------------------------------------------------------------------------------------------------------
    /// This function prints the successful loot message and all items that were looted.
    ///
    /// @param loot: the loot that was looted
    ///
    /// @return -
    //
    void printSuccessfulLoot(std::map<std::string, int>& loot);
    //------------------------------------------------------------------------------------------------------------------
    /// This function converts a decimal string to an int.
    ///
    /// @param str: string to be converted
    /// @param number: where the number should be stored
    ///
    /// @return true when conversion was successful
    /// @return false if the conversion was unsuccessful
    //
    bool decimalStringToInt_local(const std::string& str, int& number);
};

#endif
