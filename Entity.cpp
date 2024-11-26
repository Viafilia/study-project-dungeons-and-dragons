//---------------------------------------------------------------------------------------------------------------------
// Entity.cpp
//
// This is a source file for the entity class, which is the parent class for all the other subgroups, like e.g door.
//
// Group: 090
//
// Author: Julia Jesenko, 12312254
//---------------------------------------------------------------------------------------------------------------------
//
#include "Entity.hpp"

Entity::Entity()
{
  is_alive_ = true;
}

void Entity::getDamage(DamageType type, int damage)
{
  if(type == DamageType::NONE)
  {
    std::cout << "why are we in the base class?" << std::endl;
    std::cout << damage << std::endl;
  }
}

void Entity::print() const
{
  std::cout << "entity?";
}

std::pair<int,int> Entity::getPosition()
{
  return position_;
};

std::string Entity::getAbbrev()
{
  return abbreviation_;
}

void Entity::setPosition(int row, int col)
{
  position_.first = row;
  position_.second = col;
}

bool Entity::getAliveStatus()
{
  return is_alive_;
}

EntityType Entity::getEntityType()
{
  return EntityType::ENTITY;
}