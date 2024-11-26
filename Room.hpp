//---------------------------------------------------------------------------------------------------------------------
// Room.hpp
//
// This is a header file for the room class, which has all the attributes that are needed to be able to create a room.
//
// Group: 090
//
// Author: Julia Jesenko, 12312254, Maryia Filipovich 12328063
//---------------------------------------------------------------------------------------------------------------------
//
#ifndef ROOM_HPP
#define ROOM_HPP

#include "Enemy.hpp"
#include "Door.hpp"
#include "TreasureChest.hpp"
#include "Player.hpp"
#include "ItemsList.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "Story.hpp"
#include <set>

class Room
{
  private:
  int room_id_;
  bool first_entry_ = 0;
  int width_;
  int height_;
  bool lich_dead_;
  std::vector<std::vector<Entity*>> fields_;
  std::vector<Enemy*> enemies_;
  std::vector<Player*> players_;
  Door* entry_point_;
  Door* exit_door_;
  bool completed_;

  public:
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The constructor splits the input string and correctly initialises the class members.
    ///
    /// @param line The string, which contains all the information of a room
    //
    Room(std::string line);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// We do not allow initializing one Room object to another one.
    //
    Room(const Room&) = delete;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The destructor of the room class, that deletes a player from the room, if he is still alive and goes over the
    /// whole fields_ 2D-vector and deletes the entity that is there, if it is not a nullptr
    //
    ~Room();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function prints the current room
    ///
    /// @param none
    ///
    /// @return nothing
    //
    void output();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function sorts the enemy vectors and combines them into one, where everything is in the right order.
    ///
    /// @param zombies, the unsorted zombies vector
    /// @param lichs the unsorted lich vector
    /// @param goblins the unsorted goblins vector
    ///
    /// @return the sorted enemy vector
    //
    std::vector<Enemy*> addEnemies(std::vector<Enemy*> zombies, std::vector<Enemy*> lichs, std::vector<Enemy*> goblins);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function overloads the ostream and outputs the map.
    ///
    /// @param stream a reference to the ostream
    /// @param r a reference to the current room
    ///
    /// @return the overloaded ostream
    //
    friend std::ostream& operator<<(std::ostream& stream , Room &r);

    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the room id.
    ///
    /// @param none
    ///
    /// @return the room_id_ member
    //
    int getNumber();
    
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function prints the stats of the enemies.
    ///
    /// @param none
    ///
    /// @return nothing
    //
    void printEnemyStats();

    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function gets a string and a delimiter and splits the string. Every element gets saved in a vector
    ///
    /// @param string the string to be splitted
    /// @param delimiter the delimiter
    ///
    /// @return a vector where every element is a part of the original string without the delimiter
    //
    std::vector<std::string> splitString(std::string& string, char delimiter);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function compares the id's of two enemies and returns true, if the first id is smaller than the second.
    ///
    /// @param e1 the first enemy
    /// @param e2 the second enemy
    ///
    /// @return true if the id of the first enemy is smaller than the id of the second enemy, if this is not the case then
    /// false
    //
    bool compareId(Enemy* e1, Enemy* e2);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function places the player around the door after a room change around the door.
    ///
    /// @param players the vector that contains all players
    /// @param room_change 1 if the new room has a higher id as the last room, -1 if it is the other way
    ///
    /// @return nothing
    //
    void placePlayers(const std::vector<Player*> players, int room_change);
    //---------------------------------------------------------------------------------------------------------------------
    ///
    /// The function executes the move command.
    ///
    /// @param player the player that has to be moved
    /// @param target_row the target row of the move
    /// @param target_col the target column of the move
    /// @param story a pointer to the story class where the error messages are saved
    ///
    /// @return -2 if unsuccessfull, -1 if successfull, room_id if it is a Door
    //
    int moveExecute(Player* player, int target_row, int target_col, Story* story);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function checks if the target field is a nullptr and if the enemy can move there or if collision handling is
    /// needed.
    ///
    /// @param enemy the enemy that has to be moved
    /// @param row the current row of the enemy
    /// @param col the current column of the enemy
    ///
    /// @return nothing
    //
    void enemyValid(Enemy* enemy, int row, int col);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The checks every field around the current position of the enemy and searches for the one, where the target number
    /// matches.
    ///
    /// @param enemy the enemy that has to be moved
    /// @param row the current row of the enemy
    /// @param col the current column of the enemy
    /// @param target_number The number of the target field
    ///
    /// @return nothing
    //
    void enemyExecuteMove(Enemy* enemy, int row, int col, int target_number);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function checks if the given position is in bounds of this room
    ///
    /// @param pos pait of coordinates of tis pposition
    ///
    /// @return 1 if it is in the room, 0 otherwise
    //
    bool checkPosition(std::pair<int, int> pos);
    
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function makes damage to a character standing on this position
    ///
    /// @param poisition poisition where damage is put
    /// @param type type of damage that is put
    /// @param damage amount of this damage
    ///
    /// @return 1 if it was posible, 0 otherwise
    //
    bool makeDamage(std::pair<int, int> position, DamageType type, int damage);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function checks if the room was already entered by players
    ///
    /// @param -
    ///
    /// @return 1 if wasnt, 0 if was
    //
    bool notEntered();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function sets that the room was entered
    ///
    /// @param -
    ///
    /// @return -
    //
    void setEntered();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function sets that the room was completed
    ///
    /// @param -
    ///
    /// @return -
    //
    void setCompletion();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function gets a set of strings with the abbreviations of the enemies in the room
    ///
    /// @param -
    ///
    /// @return set of enemy abbreviations
    //
    std::set<std::string> getEnemyTypes();

    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the height member
    ///
    /// @return the height_ member
    //
    int getHeight();
    
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the width member
    ///
    /// @return the width_ member
    //
    int getWidth();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the fields member
    ///
    /// @return the 2D fields_ member
    //
    std::vector<std::vector<Entity*>>& getFields();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Function that checks if a field exists and is a nullptr
    ///
    /// @param row row of the field
    /// @param col column of the field
    ///
    /// @return true if it exists and is a nullptr, false if it is not the case
    //
    bool checkIfExistAndIsNullPtr(int row, int col);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Function that checks how many adjacent fields a specific field has
    ///
    /// @param row row of the field
    /// @param col column of the field
    ///
    /// @return number of adjacent fields
    //
    int getNumberOfFields(int row, int col);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Function that checks how many adjacent fields an enemy at his current position has
    ///
    /// @param enemy the current enemy
    ///
    /// @return number of adjacent fields
    //
    int enemyAdjacentFields(Enemy* enemy);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function executes the enemy move
    ///
    /// @param enemy the current enemy, that has to move
    ///
    /// @return nothing
    //
    void enemyMove(Enemy* enemy);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function executes the enemy phase, where the enemies either attack or move
    ///
    /// @param none
    ///
    /// @return nothing
    //
    void enemyPhase();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the enemies vector member
    ///
    /// @param noone
    ///
    /// @return tne enemies vector member
    //
    std::vector<Enemy*> getEnemies();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function chooses the nearest player to some enemy, that will be further attacked
    ///
    /// @param enemy that will be attacking
    ///
    /// @return player that will be attacked
    //
    Player* chosePlayerForAttack(Enemy* enemy);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function checks if the given position is in the room
    ///
    /// @param row the row coordinate
    /// @param col the collumn coordinate
    ///
    /// @return 1 if it is in the room, 0 otherwise
    //
    bool checkIfExist(int row, int col);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The executes attack of the enemy in the enemy phase
    ///
    /// @param player to attack
    /// @param enemy enemy that attacks
    ///
    /// @return 1 if attack was correct, 0 otherwise
    //
    bool attack(Player *player, Enemy* enemy);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function does the collision handling for an entity, where the player and the target
    ///
    /// @param player the current entity, that has to move
    /// @param row the current row
    /// @param col the current col
    ///
    /// @return nothing
    //
    void collisionHandling(Entity* player, int row, int col);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function moves the row pointer one row above
    ///
    /// @param row a pointer to the current row
    ///
    /// @return nothing
    //
    void moveUp(int* row);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function moves the column pointer one column to the right
    ///
    /// @param col a pointer to the current column
    ///
    /// @return nothing
    //
    void moveRight(int* col);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function moves the column pointer one column to the left
    ///
    /// @param col a pointer to the current column
    ///
    /// @return nothing
    //
    void moveLeft(int* col);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function moves the row pointer one row down
    ///
    /// @param row a pointer to the current row
    ///
    /// @return nothing
    //
    void moveDown(int* row);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function helps the function choosePlayerForAttack to choose a player based on collision handling method
    ///
    /// @param player set of players that have the same distance to an enemy and same health
    /// @param row row of the enemy
    /// @param col collumn of the enemy
    ///
    /// @return player that was the nearest
    //
    Player* findNearest(std::set<Player*> player, int row, int col);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function checks if the position is valid and there is a player from the set of players
    ///
    /// @param player set of players that have the same distance to an enemy and same health
    /// @param row row that is viewed
    /// @param col collumn that is viewed
    /// @param ans reference to a player that will store the result, which player was there
    ///
    /// @return 1 if the check was passed, 0 otherwise
    //
    bool checkIfExistAndIsInSet(std::set<Player*> player, int row, int col, Player* &ans);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function deletes enemies from the room
    ///
    /// @param -
    /// @return -
    //
    void deleteEnemies();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function checks if all enemies in the room are dead
    ///
    /// @param -
    /// @return 1 if yes, 0 otherwise
    //
    bool allEnemiesDead();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function checks if all players are dead
    ///
    /// @param -
    /// @return 1 if yes, 0 otherwise
    //
    bool allPlayersDead();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function checks if lich is dead
    ///
    /// @param -
    /// @return 1 if yes, 0 otherwise
    //
    bool lichDead();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function checks if the room was completed
    ///
    /// @param -
    /// @return 1 if yes, 0 otherwise
    //
    bool getCompletion();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function makes all dors unlocked
    ///
    /// @param -
    /// @return -
    //
    void unlockDoors();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function deletes all players in the room
    ///
    /// @param -
    /// @return -
    //
    void deletePlayers();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function gets attack position based on the weapon of the attacking enemy and desired attack position
    ///
    /// @param weapon: pointer to a weapon that enemy uses
    /// @param player_position the aiming position of attack
    /// @param player player that is the aim
    /// @param enemy emeny that attacks
    ///
    /// @return vector of positions that are attacked
    //
    std::vector<std::pair<int, int>> getAttackPositions(Weapon *weapon, std::pair<int, int> player_position,
                                                    Player *player, Enemy *enemy);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function gets a vector of weapont that the anamy can choose from based on its type and player position
    ///
    /// @param enemy: enemy that attacks
    /// @param can_melee: if the attack can be a melee attack
    /// @param items_list: pointer to the items list to get information abount the weapons
    ///
    /// @return vector of possible weapons
    //
    std::vector<Weapon *> getToChoose(Enemy *enemy, bool can_melee, ItemsList *items_list);

};

#endif