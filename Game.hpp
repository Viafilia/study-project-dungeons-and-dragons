//---------------------------------------------------------------------------------------------------------------------
//
// game class that controles the phases of the game and
//
// Group: 090
//
// Author: Maryia Filipovich 12328063, Sarah Pennauer 01331166, Julia Jesenko 12312254
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef GAME_HPP
#define GAME_HPP
#include "Dungeon.hpp"
#include "CommandParser.hpp"
#include "Player.hpp"
#include "Story.hpp"
#include "ItemsList.hpp"

#include <vector>

enum class Phase
{
  START,
  PLAYER,
  ENEMY,
  END
};

enum class EndPhase
{
  QUIT,
  DEFEAT,
  FLIGHT,
  COMPLETION,
};

class Game
{
private:
  Dungeon *dungeon_;
  ItemsList *items_list_;
  int players_amount_;
  std::vector<Player *> players_;
  int total_moves_;
  int total_action_cmd_;
  int completed_rooms_;
  Story *story_;
  Phase phase_;
  EndPhase end_phase_;

public:
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this is constuctor for the game class that sets values to the attributes
  ///
  /// @param dungeon pointer to dungeon of the game
  /// @param story pointer to story class of this game
  ///
  /// @return game
  //
  Game(Dungeon *dungeon, Story *story);
  //------------------------------------------------------------------------------------------------------------------
  ///
  /// deleted copy constuctor as we don't need to copy this class
  //
  Game(const Game &game) = delete;
  //------------------------------------------------------------------------------------------------------------------
  ///
  /// destructor of game class that deletes items_list
  //
  ~Game();
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function prints total moves amount for this game which is player amount
  ///
  /// @param -
  ///
  /// @return -
  //
  void printMoves();
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function gets pointer to the story class of this game
  ///
  /// @param -
  ///
  /// @return pointer to story class
  //
  Story *getStory();
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function starts game and prints start messages
  ///
  /// @param -
  ///
  /// @return -
  //
  void startGame();
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function starts player phase, controlles if the game should be ended and countes made actions
  ///
  /// @param -
  ///
  /// @return -
  //
  void startPlayerPhase();
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// gets pointer to player by id
  ///
  /// @param id abbreviation of the player
  ///
  /// @return pointer to the player
  //
  Player *getPlayer(std::string id);
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function asks story class to print story by given key
  ///
  /// @param key key of the story
  ///
  /// @return -
  //
  void writeStory(std::string key);
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function asks random class to roll the dice
  ///
  /// @param amount how many times to roll
  /// @param dice_type hom many sides are on the dice
  ///
  /// @return sum of the rolls
  //
  int diceRoll(int ammount, int dice_type);
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function gets active room
  ///
  /// @param -
  ///
  /// @return pointer to the room
  //
  Room *getActiveRoom();
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function helps move command to move the player
  ///
  /// @param player abbreviation of the player
  /// @param coordinates desired place in the room
  ///
  /// @return code that describes what has happened during the move
  //
  int makeMove(std::string player, std::pair<int, int> coordiantes);
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function changes activeness of the map output
  ///
  /// @param -
  ///
  /// @return -
  //
  void setOutput();
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function changes activeness of the story output
  ///
  /// @param -
  ///
  /// @return -
  //
  void setStoryOutput();
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function sets the phase to the end of the game
  ///
  /// @param -
  ///
  /// @return -
  //
  void setQuit();
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function gets vector of players in this game
  ///
  /// @param -
  ///
  /// @return players in the game
  //
  std::vector<Player *> getPlayers();
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function gets number of players
  ///
  /// @param -
  ///
  /// @return number of players
  //
  int getNumberOfPlayers();
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function starts enemy phase and ends the game if needed
  ///
  /// @param -
  ///
  /// @return -
  //
  void startEnemyPhase();
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function gets vector of enemies in active room
  ///
  /// @param -
  ///
  /// @return enemies
  //
  std::vector<Enemy *> getEnemies();
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function gets a pointer to the list of items
  ///
  /// @param -
  ///
  /// @return items list
  //
  ItemsList *getItemsList();
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function changes the amount of completed rooms
  ///
  /// @param -
  ///
  /// @return -
  //
  void completeRoom();
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function end the game and starts the end phase
  ///
  /// @param cause_of_end: EndPhase type why the end phase was triggered to output the correct messages
  ///
  /// @return -
  //
  void startEndPhase(EndPhase cause_of_end);
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function counts the score of the game
  ///
  /// @param -
  ///
  /// @return -
  //
  void gameScoring();
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function saves output of the game in the given file
  ///
  /// @param -
  ///
  /// @return -
  //
  void saveEndToFile();
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function ends the phase to the needed
  ///
  /// @param phase phase to which to change
  ///
  /// @return -
  //
  void setPhase(Phase phase);
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function sets the type of end phase
  ///
  /// @param end_phase type of phase
  ///
  /// @return -
  //
  void setEndPhase(EndPhase end_phase);
};

#endif