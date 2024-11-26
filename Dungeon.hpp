//---------------------------------------------------------------------------------------------------------------------
// Dungeon.hpp
//
// This is a header file for the dungeon class, which is needed for the whole game.
//
// Group: 090
//
// Author: Julia Jesenko, 12312254
//---------------------------------------------------------------------------------------------------------------------
//
#ifndef DUNGEON_HPP
#define DUNGEON_HPP

#include "Room.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include "Story.hpp"

class Dungeon
{
  private:
  Story* story_;
  Room* active_room_;
  std::vector<Room*> rooms_;
  std::set<std::string> printed_enemies_;
  int max_rooms_;
  bool output_active_;
  bool story_output_active_;
  std::vector<Player*> players_;

  protected:
  int completed_rooms_;

  public:
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The constructor opens the input file, reads each line and calls the room constructor and sets the other members.
    ///
    /// @param file_name The name of the file, where the config is saved
    /// @param story A pointer to the story
    //
    Dungeon(char* file_name, Story* story);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// We do not allow initializing one Dungeon object to another one.
    //
    Dungeon(const Dungeon& d) = delete;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The destructor of the dungeon class, that deletes each room. It also deletes a player, if it is not a nullptr
    /// already.
    //
    ~Dungeon();

    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Function checks how many rooms of the dungeon are already marked as "completed" and updated the dungeons
    /// "completed rooms" count.
    ///
    /// @param none
    ///
    /// @return nothing
    //
    void updateCompletedRooms();

    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Function calls the corresponding other functions to print the active room
    ///
    /// @param none
    ///
    /// @return nothing
    //
    void printRoom();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function calls the corresponding other function that are needed for a room change
    ///
    /// @param room_num the room_id of the new room
    ///
    /// @return nothing
    //
    void changeActiveRoom(int room_num);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the active room member
    ///
    /// @param none
    ///
    /// @return a pointer to the active room
    //
    Room* getActiveRoom();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Setter for the players vector member
    ///
    /// @param players a vector with all playeers
    ///
    /// @return nothing
    //
    void setPlayers(std::vector<Player*> players);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function calls the corresponding function to place the players in the active room around the door
    ///
    /// @param room_change 1 if the new room has a higher id as the previous one, -1 if it has a lower id
    ///
    /// @return nothing
    //
    void placePlayers(int room_change);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function calls the corresponding other function that are needed for a room change
    ///
    /// @param player the player that wants to move
    /// @param coordinates a pair, that contains the target row and target column
    /// @param story a pointer to the story where the error messages are stored
    ///
    /// @return return 0 if unsuccessfull, return 1 if successfull, return 2 if flight, 3 if room change
    //
    int makeMove(std::string player, std::pair<int,int> coordiantes, Story* story);
    //------------------------------------------------------------------------------------------------------------------
    /// The function sets the room output variable to the other one (true->false, false->true)
    ///
    /// @param none
    ///
    /// @return nothing
    //
    void setOutput();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function sets the story output variable to the other one (true->false, false->true)
    ///
    /// @param none
    ///
    /// @return nothing
    //
    void setStoryOutput();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function deletes all players from the player vector
    ///
    /// @param none
    ///
    /// @return nothing
    //
    void deletePlayers();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the completed rooms member
    ///
    /// @param none
    ///
    /// @return returns the completed rooms
    //
    int getCompletedRooms();
};

#endif