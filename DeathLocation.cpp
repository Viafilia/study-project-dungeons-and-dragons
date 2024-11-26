//---------------------------------------------------------------------------------------------------------------------
// DeathLocation.cpp
//
// This is the source file for the DeathLocation class, where all the methods are implemented.
//
// Group: 090
//
// Author: Sarah Pennauer 01331166
//---------------------------------------------------------------------------------------------------------------------
//

#include "DeathLocation.hpp"


  DeathLocation::DeathLocation(Inventory* dead_entity_inventory)
  {
    abbreviation_ = "X";
    death_location_loot_ = new Inventory(*dead_entity_inventory);
  }

  DeathLocation::~DeathLocation()
  {
    delete death_location_loot_;
  };

  Inventory*  DeathLocation::getDeathLocationLoot()
  {
    return death_location_loot_;
  }

  void  DeathLocation::setDeathLocationLootTrue()
  {
    is_looted_ = true;
  }

  EntityType  DeathLocation::getEntityType() 
  {
    return EntityType::DEATH_LOCATION;
  }

void DeathLocation::print() const
{
  std::cout << " " << abbreviation_ << " ";
}
