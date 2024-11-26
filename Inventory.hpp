//---------------------------------------------------------------------------------------------------------------------
// Inventory.hpp
//
// The header file contains 2 classes: the enum class InventoryType and the class Inventory. 
// The class inventory type is needed because of Death Location, where a separate Inventory is created upon death (the
// of an enemy is always the same and differs from the equipped items).
// The inventory class stores not only the current inventory of an entity, but also reference lists of the different
// item types (weapons, armor, etc.) to facilitate comparing between the two.
//
// Author: Sarah Pennauer, 01331166
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "Weapons.hpp"
#include "Potion.hpp"
#include "Ammunition.hpp"
#include "Armor.hpp"
#include "Character.hpp"

enum class InventoryType
{
  BASE,
  LOOT
};

class Inventory
{
  private:
    std::map<std::string, int> inventory_list_;
    std::vector<std::string> armor_abbrevs_;
    std::vector<std::string> weapon_abbrevs_;
    std::vector<std::string> consumable_abbrevs_;

  public:
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a constructor for an Inventory. The inventory gets created depending on the Character Type and
    /// also depending on if it is a base or a loot inventory (for when an enemy dies).
    /// The inventory list gets initialized accordingly.
    ///
    /// @param char_type_: CharacterType for which the inventory needs to be created to initialize it correctly
    /// @param inventory_type_: see enum class; base class for character creation, loot for death
    ///
    /// @return -
    //
    Inventory(CharacterType char_type_, InventoryType inventory_type_); 
    //------------------------------------------------------------------------------------------------------------------
    /// This function is the copy constructor which creates a deep copy of the object. 
    ///
    /// @param Inventory&: reference to the Inventory object 
    /// 
    /// @return -
    //    
    Inventory(const Inventory& other);
    /// This function is the destructor which is set to default. 
    ///
    /// @param -
    /// 
    /// @return -
    //  
    ~Inventory() = default; 
    //------------------------------------------------------------------------------------------------------------------
    /// This function initializes the inventory when it is created according to character type and inventory type.
    ///
    /// @param character_type: character type of the entity being created (i.e. wizard)
    /// @param inventory_type: the inventory type that needs to be created (base upon creation of character and loot
    ///                        upon creation of death location)
    /// @return -
    //
    void initializeBaseInventory(CharacterType character_type, InventoryType inventory_type);
    //------------------------------------------------------------------------------------------------------------------
    /// This function changes the amount of a specific item the entity has in their posession by a specific value.
    ///
    /// @param item: the abbreviation of the item the amount has to be changed of
    /// @param amount_change: the amount that needs to be added to or subtracted from the current possession-amount 
    /// @return true on success
    /// @return false if the amount_change cannot be taken away from the amount (taking 1 where there is 0) or the 
    ///         item could not be found
    //
    bool changeInventoryItemAmount(std::string item, int amount_change);
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a Getter-Method for the inventory map of the entity, containing a list of all items + the 
    /// amount the entity has.
    ///
    /// @param -
    /// @return inventory-list
    //
    std::map<std::string, int> getInventoryList();
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a Getter-Method for the Armor-list (the list containing all armor abbreviations).
    ///
    /// @param -
    /// @return armor-list
    //
    std::vector<std::string> getArmorList();
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a Getter-Method for the weapons-list (the list containing all weapon abbreviations).
    ///
    /// @param -
    /// @return weapons-list
    //
    std::vector<std::string> getWeaponList();
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a Getter-Method for the consumables-list (the list containing all consumables abbreviations).
    ///
    /// @param -
    /// @return consumables-list
    //
    std::vector<std::string> getConsumableList();
};

#endif