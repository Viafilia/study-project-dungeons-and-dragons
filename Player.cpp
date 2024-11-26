//---------------------------------------------------------------------------------------------------------------------
// Player.cpp
//
// This is the source file of the player class, where all the methods are implemented.
//
// Group: 090
//
// Author: Julia Jesenko, 12312254
//---------------------------------------------------------------------------------------------------------------------
//
#include "Player.hpp"
#include "Weapons.hpp"
#include <algorithm>

Player::Player(std::string name, std::string type, int id)
{
  name_ = name;
  id_ = id;
  if (type == "b")
  {
    type_ = CharacterType::BARBARIAN;
    type_name_ = "Barbarian";
    abbreviation_ = "B";
    strength_ = 4;
    vitality_ = 1;
    max_health_ = 12 + vitality_;
    health_ = max_health_;
    armour_value_ = 2;
    is_alive_ = true;
  }
  else if (type == "r")
  {
    type_ = CharacterType::ROGUE;
    type_name_ = "Rogue";
    abbreviation_ = "R";
    strength_ = 2;
    vitality_ = 3;
    max_health_ = 8 + vitality_; // + Vitality
    health_ = max_health_;
    armour_value_ = 1;
    is_alive_ = true;
  }
  else if (type == "w")
  {
    type_ = CharacterType::WIZARD;
    type_name_ = "Wizard";
    abbreviation_ = "W";
    strength_ = 1;
    vitality_ = 4;
    max_health_ = 6 + vitality_; // + Vitality
    health_ = max_health_;
    armour_value_ = 0;
    is_alive_ = true;
  }
  equiped_weapon_ = nullptr;
  equiped_armor_ = nullptr;
  inventory_ = new Inventory(type_, InventoryType::BASE);
}

Player::~Player()
{
  delete inventory_;
}

std::pair<int,int> Player::getPosition()
{
  return position_;
}

void Player::printPosition()
{
  std::cout << type_name_ << " [" << abbreviation_ << "] \"" << name_ << "\" on (" << position_.first + 1 << "," <<
  position_.second + 1 << ")" << std::endl;
}

void Player::printMoveMessage()
{
  std::cout << type_name_ << " [" << abbreviation_ << "] \"" << name_ << "\" moved to (" << 
  position_.first + 1 << "," << position_.second + 1 << ")." << std::endl;
}

Inventory* Player::getInventory()
{
  return inventory_;
}

Armor* Player::getEquippedArmor()
{
  return equiped_armor_;
}

Inventory* Player::getDeathInventory()
{
  return inventory_;
}

EntityType Player::getEntityType()
{
  return EntityType::PLAYER;
}

void Player::printBanner() const
{
  std::cout << "  Player " << id_ << ": " << type_name_ << " [" << abbreviation_ << "] \"" << name_ << "\"" << std::endl;
}

void Player::print() const
{
  std::cout << " " << abbreviation_ << " ";
}

bool Player::changeItemAmount(std::string item, int amount_change)
{
  return inventory_->changeInventoryItemAmount(item, amount_change);
}

std::string Player::getName()
{
  return name_;
}

std::string Player::getTypeName()
{
  return type_name_;
}

int Player::getHealth()
{
  return health_;
}
int Player::getMaxHealth()
{
  return max_health_;
}
void Player::setResistance(const DamageType &type)
{
  resistance_ = type;
}

bool Player::equipWeapon(Weapon *weapon)
{

  if (equiped_weapon_ != nullptr)
  {
    inventory_->changeInventoryItemAmount(equiped_weapon_->getAbbreviation(), 1);
  }
  equiped_weapon_ = weapon;
  return 1;
}

bool Player::equipArmor(Armor *armor)
{

  if (equiped_armor_ != nullptr)
  {
    inventory_->changeInventoryItemAmount(equiped_armor_->getAbbreviation(), 1);
  }
  equiped_armor_ = armor;
  return 1;
}

Weapon *Player::getWeapon()
{
  return equiped_weapon_;
}

int Player::addHealth(int to_add)
{
  to_add = std::min(max_health_ - health_, to_add);
  health_ += to_add;
  return to_add;
}

int Player::calcArmor()
{
  int res = armour_value_;
  if (equiped_armor_ != nullptr)
  {
    if (equiped_armor_->getAbbreviation() == "LARM")
    {
      res = std::max(res, 1 + vitality_);
    }
    if (equiped_armor_->getAbbreviation() == "BPLT")
    {
      res = std::max(res, 4 + std::min(vitality_, 2));
    }
    if (equiped_armor_->getAbbreviation() == "CHML")
    {
      res = std::max(res, 6);
    }
    if (equiped_armor_->getAbbreviation() == "PARM")
    {
      res = std::max(res, 8);
    }
  }
  return res;
}

std::string Player::getAbbreviation()
{
  return abbreviation_;
}

void Player::die()
{
  is_alive_ = false;

  std::string armor; 
  std::string weapon;
  //you can use equip(nullptr) it will work
  if(equiped_armor_ != nullptr)
  {
    armor = equiped_armor_->getAbbreviation();
    inventory_->changeInventoryItemAmount(armor, 1);
  }
  if(equiped_weapon_ != nullptr)
  {
    weapon = equiped_weapon_->getAbbreviation();
    inventory_->changeInventoryItemAmount(weapon, 1);
  }
}