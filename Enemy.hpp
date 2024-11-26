//---------------------------------------------------------------------------------------------------------------------
// Enemy.hpp
//
// This is a header file for the enemy class, which is derived from the character class.
//
// Group: 090
//
// Author: Julia Jesenko, 12312254
//---------------------------------------------------------------------------------------------------------------------
//
#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <vector>
#include <utility>
#include "Character.hpp"
#include "Inventory.hpp"
#include <iostream>

class Enemy : public Character
{
  private:
  Inventory* inventory_;
  Inventory* loot_inventory_;
  CharacterType type_;
  std::string name_;
  int id_;
  static bool is_printed_;

  public:
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The constructor of the enemy class, sets the members with the correct values.
    ///
    /// @param id the enemy id
    /// @param row row position number
    /// @param col column position number
    /// @param type the enemy type
    //
    Enemy(int id, int row, int col, int type);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// We do not allow initializing one enemy object to another one.
    //
    Enemy(const Enemy& e) = delete;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The destructor deletes the two inventory pointers.
    //
    ~Enemy();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function prints the enemy symbol, with the id.
    ///
    /// @param none
    ///
    /// @return nothing
    //
    void print() const override;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function prints the health of the enemies.
    ///
    /// @param none
    ///
    /// @return nothing
    //
    void printStats() const;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the armor amount member
    ///
    /// @param none
    ///
    /// @return the armor amount member
    //
    int calcArmor() override;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the id member
    ///
    /// @param none
    ///
    /// @return the id member
    //
    int getId();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function prints the current position of the enemy
    ///
    /// @param none
    ///
    /// @return nothing
    //
    void printPosition();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the name member
    ///
    /// @param none
    ///
    /// @return the name member
    //
    std::string getName() override;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function updates the health of an enemy accordingly
    ///
    /// @param none
    ///
    /// @return nothing
    //
    void updateHealth();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the abbreviation member
    ///
    /// @param none
    ///
    /// @return the abbreviation
    //
    std::string getAbbrev() override;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the enemy type member
    ///
    /// @param none
    ///
    /// @return the enemy type
    //
    CharacterType getType();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function prints the move message that appears after an enemy moved.
    ///
    /// @param none
    ///
    /// @return none
    //
    void printMoveMessage();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function prints the move message that appears after an enemy moved.
    ///
    /// @param none
    ///
    /// @return none
    //
    void die() override;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the loot inventory.
    ///
    /// @param none
    ///
    /// @return a pointer to the loot inventory
    //
    Inventory* getDeathInventory();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Returns that it is an enemy
    ///
    /// @param none
    ///
    /// @return the entity type enemy
    //
    EntityType getEntityType() override;

};

#endif