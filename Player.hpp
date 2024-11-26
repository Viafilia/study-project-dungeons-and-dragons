//---------------------------------------------------------------------------------------------------------------------
// Player.hpp
//
// This is a header file for the player class, which is derived from the entity class.
//
// Group: 090
//
// Author: Julia Jesenko, 12312254
//---------------------------------------------------------------------------------------------------------------------
//
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>
#include "Character.hpp"
#include "Inventory.hpp"


class Player : public Character
{
  private:
  Inventory* inventory_;
  std::string name_;
  CharacterType type_;
  std::string type_name_;
  Weapon* equiped_weapon_;
  Armor* equiped_armor_;
  int id_;

  public:
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The constructor of the player class, where all the attributes are added ,depending on the type.
    ///
    /// @param name the name of the player
    /// @param type the type of the player
    /// @param id the player id
    //
    Player(std::string name, std::string type, int id);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// We do not allow initializing one Room object to another one.
    //
    Player(const Player& p) = delete;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The destructor of the player class, where the inventory pointer gets deleted.
    //
    ~Player();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function prints the player that gets printed at the start of the game-
    ///
    /// @param -
    ///
    /// @return -
    //
    void printBanner() const;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function prints the player symbol.
    ///
    /// @param -
    ///
    /// @return -
    //
    void print() const override;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the position member.
    ///
    /// @param -
    ///
    /// @return the position member
    //
    std::pair<int,int> getPosition() override;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function prints the current position of the player
    ///
    /// @param -
    ///
    /// @return -
    //
    void printPosition();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function prints the move message, tht gets printed when a player moves.
    ///
    /// @param -
    ///
    /// @return -
    //
    void printMoveMessage();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function changes the item amount of a specific item of the player
    ///
    /// @param item the item, which amount should be changed
    /// @param amount_change the amount, that should be added or decreased
    ///
    /// @return true on success false if the amount_change cannot be taken away from the amount
    /// (taking 1 where there is 0) or the item could not be found
    //
    bool changeItemAmount(std::string item, int amount_change);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Returns the current armor amount, that is different depending on the equipped armor.
    ///
    /// @param -
    ///
    /// @return the armor amount
    //
    int calcArmor() override;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the name of the player
    ///
    /// @param -
    ///
    /// @return the name of the player
    //
    std::string getName() override;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the abbreviation of the player
    ///
    /// @param -
    ///
    /// @return the abbreviation of the player
    //
    std::string getAbbreviation();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the type name of the player
    ///
    /// @param -
    ///
    /// @return the type name
    //
    std::string getTypeName();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the current health of the player
    ///
    /// @param -
    ///
    /// @return the current health
    //
    int getHealth();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the maximum health of the player
    ///
    /// @param -
    ///
    /// @return the maximum health of the player
    //
    int getMaxHealth();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the current weapon of the player
    ///
    /// @param -
    ///
    /// @return a pointer to the current equipped weapon
    //
    Weapon* getWeapon();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Sets the resistance of the player to a specific type
    ///
    /// @param type a reference to the type, that the player should be resistant to
    ///
    /// @return -
    //
    void setResistance(const DamageType &type);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// A function to equip a new weapon
    ///
    /// @param weapon a pointer to the new weapon that should be equipped
    ///
    /// @return always true
    //
    bool equipWeapon(Weapon* weapon);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// A function to equip a new armor
    ///
    /// @param weapon a pointer to the new armor that should be equipped
    ///
    /// @return always true
    //
    bool equipArmor(Armor* armor);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the current inventory of the player
    ///
    /// @param -
    ///
    /// @return a pointer to the current inventory of the player
    //
    Inventory* getInventory();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the current armor of the player
    ///
    /// @param -
    ///
    /// @return a pointer to the current equipped armor of the player
    //
    Armor* getEquippedArmor();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function handels the death of a player and changes their alive status to false and gives the current armor
    /// and current weapon in the inventory.
    ///
    /// @param -
    ///
    /// @return a pointer to the current equipped weapon
    //
    void die() override;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the inventory of the player
    ///
    /// @param -
    ///
    /// @return a pointer to the inventory of a player
    //
    Inventory* getDeathInventory();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Returns tha the entity type is a player
    ///
    /// @param -
    ///
    /// @return the entity type player
    //
    EntityType getEntityType() override;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// A function to add health to the current health amount, depending on how much HP are missing to the max. health.
    ///
    /// @param to_add how much health should be added
    ///
    /// @return how much health was actually added, because overheal is not possible
    //
    int addHealth(int to_add);
};



#endif