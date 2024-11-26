//---------------------------------------------------------------------------------------------------------------------
//
// DisplayCmd.hpp
//
// The header file for the DisplayCmd class, which is derived from the Command class. 
// This class executes all display commands, that are entered by a user depending on its type
//
// Group: 090
//
// Author: Maryia Filipovich 12328063, Sarah Pennauer 01331166, Julia Jesenko 12312254
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef DISPLAYCOMMAND_HPP
#define DISPLAYCOMMAND_HPP

#include <string>
#include <fstream>
#include "Command.hpp"

class DisplayCmd : public Command
{
  protected: 
    CommandType type_;
    std::string player_type_abbrev_;

  public: 
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a constructor for a Display Command to get access to the display methods. 
    ///
    /// @param -
    ///
    /// @return -
    //
    DisplayCmd() {};
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a constructor for a Display Command. 
    ///
    /// @param type: the type of display cmd (i.e. "help")
    /// @param vectorized_input: the user input minus the cmd part split in strings
    /// @param num_of_params: number of params (= number of strings in the vectorized_input)
    /// @param game: pointer to the game object
    ///
    /// @return -
    //
    DisplayCmd(CommandType type, std::vector<std::string> vectorized_input, int num_of_params, Game* game);
    //------------------------------------------------------------------------------------------------------------------
    /// This function is the copy constructor which gets deleted explicitely. 
    ///
    /// @param DisplayCmd&: reference to the DisplayCmd object 
    /// 
    /// @return -
    //   
    DisplayCmd(const DisplayCmd&) = delete;
    //------------------------------------------------------------------------------------------------------------------
    /// This function is the destructor which is set to default. 
    ///
    /// @param -
    /// 
    /// @return -
    //   
    ~DisplayCmd() = default;

    //------------------------------------------------------------------------------------------------------------------
    ///
    /// In this function the display function corresponding to the user input is called.
    ///
    /// @param -
    ///
    /// @return true on success
    /// @return false in case of invalid cmd
    //
    bool execute() override;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// In this function the print help text function gets called.
    ///
    /// @param -
    ///
    /// @return nothing
    //
    bool executeHelpCmd();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// In this function the prints the help text.
    ///
    /// @param -
    ///
    /// @return nothing
    //
    void printHelp();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// In this function the corresponding functions are called to change the story output.
    ///
    /// @param -
    ///
    /// @return true on success
    //
    bool executeStoryCmd();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// In this function the corresponding functions are called to change the map output.
    ///
    /// @param -
    ///
    /// @return true on success
    //
    bool executeMapCmd();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// In this function the positions of all players and enemies are printed.
    ///
    /// @param -
    ///
    /// @return true on success
    //
    bool executePosCmd();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// In this function the information about the particular player is printed
    ///
    /// @param -
    ///
    /// @return true on success
    //
    bool executePlayerCmd();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// This function is the execute function for the inventory command.
    /// It first checks, if the command parameters are valid and then it prints the player's currently equipped armor +
    /// weapon and then the rest of the inventory sorted by item types.
    ///
    /// @param -
    ///
    /// @return true on success
    //
    bool executeInventoryCmd();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// This function compares the inventory of a player to the reference list and if there is a match, prints the title
    /// and the inventory-contents of that specific item type.
    ///
    /// @param list_name: the name of the list that is looked through (i.e. "Weapons")
    /// @param inventory_list: the inventory list of the player's inventory (meaning a map of all inventory items and 
    ///                        the corresponding amount)
    /// @param ref_list: the reference list to which the inventory list is compared to (i.e. a list of all weapons).
    ///
    /// @return -
    //
    void printPlayerInventory(std::string list_name, std::map<std::string, int>& inventory_list, 
                              std::vector<std::string>& ref_list);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// This function checks if items of one list can be found in another, or if there are no common items.
    ///
    /// @param ref_list: the reference list to which the inventory list is compared to (i.e. a list of all weapons).
    /// @param inventory_list: the inventory list of the player's inventory (meaning a map of all inventory items and 
    ///                        the corresponding amount)
    /// @return true if an item was found that exists in both lists
    //
    bool checkListContents(std::vector<std::string>& ref_list, std::map<std::string, int>& inventory_list);
};

#endif
