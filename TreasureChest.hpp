//---------------------------------------------------------------------------------------------------------------------
// TreasureChest.hpp
//
// The header file contains the Treasure Chest class, which is derived from Entity.
//
// Group: 090
//
// Author: Sarah Pennauer, Julia Jesenko
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef TREASURECHEST_HPP
#define TREASURECHEST_HPP

#include <vector>
#include <utility>
#include <sstream>
#include <algorithm>

#include "Entity.hpp"
#include "Inventory.hpp"

class TreasureChest : public Entity
{
private:
  Inventory *chest_loot_ = new Inventory(CharacterType::CHEST, InventoryType::BASE);
  bool is_locked_;
  int value_needed_to_unlock_;

public:
  //------------------------------------------------------------------------------------------------------------------
  /// This function is a constructor for a Treasure Chest.
  ///
  /// @param row: row (position) of the chest on the map
  /// @param col: column (position) of the chest on the map
  /// @param items: string of the items in the chest that is split up and saved into inventory
  /// @param unlock_value_extract: the value the player has to roll to unlock the chest
  ///
  /// @return -
  //
  TreasureChest(int row, int col, std::string items, std::string unlock_value_extract);
  //------------------------------------------------------------------------------------------------------------------
  /// This function is the copy constructor which is set to default.
  ///
  /// @param TreasureChest&: reference to the TreasureChest object
  ///
  /// @return -
  //
  TreasureChest(const TreasureChest &) = default;
  //------------------------------------------------------------------------------------------------------------------
  /// This function is the destructor which is set to default.
  ///
  /// @param -
  ///
  /// @return -
  //
  ~TreasureChest();
  //------------------------------------------------------------------------------------------------------------------
  /// This function prints the Chest's abbreviation.
  ///
  /// @param -
  ///
  /// @return -
  //
  void print() const override;
  //------------------------------------------------------------------------------------------------------------------
  /// This function takes the item string from the constructor, splits it up and fills the chest's inventory
  /// accordingly.
  ///
  /// @param vectorized_chest_items: the string from the config file containing the chest items as string
  ///
  /// @return -
  //
  void fillChest(std::vector<std::string> &vectorized_chest_items);
  //------------------------------------------------------------------------------------------------------------------
  /// This is a Getter Method for the value the player needs to roll to unlock the chest.
  ///
  /// @param -
  ///
  /// @return the value the player needs to unlock the chest
  //
  int getValueToUnlock();
  //------------------------------------------------------------------------------------------------------------------
  /// This is a Getter Method for the chest inventory.
  ///
  /// @param -
  ///
  /// @return pointer to the chest inventory
  //
  Inventory *getChestLoot();
  //------------------------------------------------------------------------------------------------------------------
  /// This is a Getter Method for the entity type.
  ///
  /// @param -
  ///
  /// @return EntityType Chest
  //
  EntityType getEntityType() override;
};

#endif