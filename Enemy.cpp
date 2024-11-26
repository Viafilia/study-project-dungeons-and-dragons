//---------------------------------------------------------------------------------------------------------------------
// Enemy.cpp
//
// This is the source file of the enemy class, where all the methods are implemented.
//
// Group: 090
//
// Author: Julia Jesenko, 12312254
//---------------------------------------------------------------------------------------------------------------------
//
#include "Enemy.hpp"
#include "Random.hpp"

Enemy::Enemy(int id, int row, int col, int type)
{
  id_ = id;
  if (type == 0)
  {
    type_ = CharacterType::ZOMBIE;
    health_ = 15;
    name_ = "Zombie";
    strength_ = 3;
    vitality_ = 0;
    max_health_ = 15;
    vitality_ = 0;
    strength_ = 3;
    armour_value_ = 1;
    abbreviation_ = "Z";
    is_alive_ = true;
    loot_inventory_ = new Inventory(CharacterType::ZOMBIE, InventoryType::LOOT);
  }
  if (type == 1)
  {
    type_ = CharacterType::GOBLIN;
    health_ = 10;
    name_ = "Goblin";
    strength_ = 3;
    vitality_ = 4;
    max_health_ = 10;
    vitality_ = 4;
    strength_ = 3;
    armour_value_ = 4;
    abbreviation_ = "G";
    is_alive_ = true;
    loot_inventory_ = new Inventory(CharacterType::GOBLIN, InventoryType::LOOT);
  }
  if (type == 2)
  {
    type_ = CharacterType::LICH;
    health_ = 50;
    name_ = "Lich";
    strength_ = 2;
    vitality_ = 8;
    max_health_ = 50;
    vitality_ = 8;
    strength_ = 2;
    armour_value_ = 6;
    abbreviation_ = "L";
    is_alive_ = true;
    resistance_ = DamageType::COLD;
    loot_inventory_ = new Inventory(CharacterType::LICH, InventoryType::LOOT);
  }
  position_ = std::pair<int, int>(row, col);
  inventory_ = new Inventory(type_, InventoryType::BASE);
}

void Enemy::print() const
{
  if (type_ == CharacterType::ZOMBIE)
  {
    std::cout << " Z" << id_;
  }
  else if (type_ == CharacterType::GOBLIN)
  {
    std::cout << " G" << id_;
  }
  else if (type_ == CharacterType::LICH)
  {
    std::cout << " L" << id_;
  }
}

void Enemy::printStats() const
{
  if (type_ == CharacterType::ZOMBIE)
  {
    std::cout << " Z" << id_ << ": " << health_ << "/" << max_health_;
  }
  else if (type_ == CharacterType::GOBLIN)
  {
    std::cout << " G" << id_ << ": " << health_ << "/" << max_health_;
  }
  else if (type_ == CharacterType::LICH)
  {
    std::cout << " L" << id_ << ": " << health_ << "/" << max_health_;
  }
}

int Enemy::calcArmor()
{
  return armour_value_;
}

std::string Enemy::getName()
{
  std::string res = name_;
  res += " " + std::to_string(id_);
  return res;
}

EntityType Enemy::getEntityType()
{
  return EntityType::ENEMY;
}

Inventory *Enemy::getDeathInventory()
{
  return loot_inventory_;
}

void Enemy::die()
{
  is_alive_ = false;
}

void Enemy::printMoveMessage()
{
  std::string type;
  if (type_ == CharacterType::ZOMBIE)
  {
    type = "Zombie";
  }
  if (type_ == CharacterType::GOBLIN)
  {
    type = "Goblin";
  }
  if (type_ == CharacterType::LICH)
  {
    type = "Lich";
  }
  std::cout << '\n'
            << type << " " << id_ << " [" << abbreviation_ << id_ << "] moved to (" << position_.first + 1 << "," << 
            position_.second + 1 << ")." << std::endl;
}

CharacterType Enemy::getType()
{
  return type_;
}

std::string Enemy::getAbbrev()
{
  return abbreviation_;
}

void Enemy::printPosition()
{
  std::string type;
  if (type_ == CharacterType::ZOMBIE)
  {
    type = "Zombie";
  }
  if (type_ == CharacterType::GOBLIN)
  {
    type = "Goblin";
  }
  if (type_ == CharacterType::LICH)
  {
    type = "Lich";
  }
  std::cout << type << " " << id_ << " [" << abbreviation_ << id_ << "] on (" << position_.first + 1 << "," << 
               position_.second + 1 << ")" << std::endl;
}

int Enemy::getId()
{
  return id_;
}

Enemy::~Enemy()
{
  delete inventory_;
  delete loot_inventory_;
};