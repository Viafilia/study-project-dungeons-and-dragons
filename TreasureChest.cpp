//---------------------------------------------------------------------------------------------------------------------
// TreasureChest.cpp
//
// This is the source file for the TreasureChest class.
//
// Group: 090
//
// Author: Sarah Pennauer 01331166, Julia Jesenko 12312254
//---------------------------------------------------------------------------------------------------------------------
//

#include "TreasureChest.hpp"

TreasureChest::TreasureChest(int row, int col, std::string items, std::string unlock_value_extract)
{
  abbreviation_ = "T";
  is_locked_ = true;
  position_ = std::pair<int, int>(row, col);
  std::vector<std::string> vectorized_chest_items;
  std::stringstream item_string(items);
  std::string token;
  while (std::getline(item_string, token, ','))
  {
    transform(token.begin(), token.end(), token.begin(), ::tolower);
    vectorized_chest_items.push_back(token);
  };

  std::stringstream unlock(unlock_value_extract);
  std::vector<std::string> vectorized_unlock_value;
  while (std::getline(unlock, token, ':'))
  {
    vectorized_unlock_value.push_back(token);
  }
  value_needed_to_unlock_ = stoi(vectorized_unlock_value.at(2));

  fillChest(vectorized_chest_items);
}

TreasureChest::~TreasureChest()
{
  delete chest_loot_;
}

int TreasureChest::getValueToUnlock()
{
  return value_needed_to_unlock_;
}

Inventory *TreasureChest::getChestLoot()
{
  return chest_loot_;
}

EntityType TreasureChest::getEntityType()
{
  return EntityType::CHEST;
}

void TreasureChest::print() const
{
  if (is_locked_ == true)
  {
    std::cout << "#T ";
  }
  else
  {
    std::cout << " T ";
  }
}

void TreasureChest::fillChest(std::vector<std::string> &vectorized_chest_items)
{
  int num_of_item_pairs = vectorized_chest_items.size();
  for (int i = 0; i < num_of_item_pairs; i++)
  {
    if (i % 2 == 0)
    {
      std::string item_in_chest = vectorized_chest_items.at(i);
      std::transform(item_in_chest.begin(), item_in_chest.end(), item_in_chest.begin(), ::toupper);
      int added_amount = std::stoi(vectorized_chest_items.at(i + 1));
      chest_loot_->changeInventoryItemAmount(item_in_chest, added_amount);
    }
  }
}