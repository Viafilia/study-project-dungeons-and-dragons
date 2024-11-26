//---------------------------------------------------------------------------------------------------------------------
// Room.cpp
//
// This is the source file for the room class, where all the methods are implemented.
//
// Group: 090
//
// Author: Julia Jesenko 12312254, Maryia Filipovich 12328063
//---------------------------------------------------------------------------------------------------------------------
//
#include "Room.hpp"
#include "Random.hpp"
#include "DeathLocation.hpp"
#include "ItemsList.hpp"
#include <cmath>

#include <algorithm>

int diceRoll(int amount, int dice_type)
{
  int sum = 0;
  for (int i = 0; i < amount; i++)
  {
    sum += Oop::Random::getInstance().getRandomNumber(dice_type);
  }
  std::cout << "[Dice Roll] " << amount << " d" << dice_type << " resulting in a total value of " << sum << ".\n\n";
  return sum;
}

Room::Room(std::string line)
{
  lich_dead_ = 0;
  exit_door_ = nullptr;
  completed_ = false;
  std::vector<std::string> token = splitString(line, ';');
  int room_id = token.at(0).at(0) - 48;
  room_id_ = room_id;
  int width = token.at(0).at(2) - 48;
  width_ = width;
  int height = token.at(0).at(4) - 48;
  height_ = height;
  std::vector<Enemy *> zombies;
  std::vector<Enemy *> goblins;
  std::vector<Enemy *> lichs;
  std::vector<std::vector<Entity *>> test_fields(height, std::vector<Entity *>(width));
  for (std::vector<Entity *> &entity : test_fields)
  {
    std::vector<Entity *> field;
    for (auto &element : entity)
    {
      element = nullptr;
      field.push_back(element);
    }
  }
  for (auto c : token)
  {
    int row = c.at(2) - 48;
    int col = c.at(4) - 48;
    if (c.at(0) == 'D')
    {
      int door_id = c.at(6) - 48;
      Door *door = new Door(door_id, row - 1, col - 1);
      test_fields[row - 1][col - 1] = door;
      if (door_id == room_id_ - 1)
      {
        entry_point_ = door;
      }
      else if (door_id == room_id_ + 1)
      {
        exit_door_ = door;
      }
    }
    else if (c.at(0) == 'Z')
    {
      int enemy_id = c.at(6) - 48;
      Enemy *zombie = new Enemy(enemy_id, row - 1, col - 1, 0);
      test_fields[row - 1][col - 1] = zombie;
      zombies.push_back(zombie);
    }
    else if (c.at(0) == 'G')
    {
      int enemy_id = c.at(6) - 48;
      Enemy *goblin = new Enemy(enemy_id, row - 1, col - 1, 1);
      test_fields[row - 1][col - 1] = goblin;
      goblins.push_back(goblin);
    }
    else if (c.at(0) == 'L')
    {
      int enemy_id = c.at(6) - 48;
      Enemy *lich = new Enemy(enemy_id, row - 1, col - 1, 2);
      test_fields[row - 1][col - 1] = lich;
      lichs.push_back(lich);
    }
    else if (c.at(0) == 'T')
    {
      std::string items = c;
      std::vector<std::string> test = splitString(items, ':');
      int first_comma_location = test.at(2).find(',');
      std::string only_items = test.at(2).substr(first_comma_location + 1);
      test_fields[row - 1][col - 1] = new TreasureChest(row - 1, col - 1, only_items, items);
    }
  }
  enemies_ = addEnemies(zombies, lichs, goblins);
  fields_ = test_fields;
}

std::vector<Enemy *> Room::addEnemies(std::vector<Enemy *> zombies, std::vector<Enemy *> lichs, std::vector<Enemy *> goblins)
{
  std::vector<Enemy *> test_enemies;
  std::sort(zombies.begin(), zombies.end(), [](Enemy *e1, Enemy *e2)
            { return (e1->getId() < e2->getId()); });
  std::sort(goblins.begin(), goblins.end(), [](Enemy *e1, Enemy *e2)
            { return (e1->getId() < e2->getId()); });
  std::sort(lichs.begin(), lichs.end(), [](Enemy *e1, Enemy *e2)
            { return (e1->getId() < e2->getId()); });

  for (auto c : goblins)
  {
    test_enemies.push_back(c);
  }
  for (auto c : lichs)
  {
    test_enemies.push_back(c);
  }
  for (auto c : zombies)
  {
    test_enemies.push_back(c);
  }
  return test_enemies;
}

bool Room::getCompletion()
{
  return completed_;
}

std::ostream &operator<<(std::ostream &out, Room &r)
{

  out << "   ";
  for (int j = 1; j <= r.width_; j++)
  {
    std::cout << "  " << j << " ";
    if (j == r.width_)
    {
      out << " " << std::endl;
    }
  }
  int row_num = 1;
  out << "   +";
  for (int i = 0; i < r.width_; i++)
  {
    out << "---+";
  }
  out << "\n";
  for (std::vector<Entity *> &entity : r.fields_)
  {
    out << " " << row_num << " |";
    for (auto &element : entity)
    {
      if (element == nullptr)
      {
        out << "   ";
      }
      else
      {
        element->print();
      }
      out << "|";
    }
    out << std::endl;
    out << "   +";
    for (int i = 0; i < r.width_; i++)
    {
      out << "---+";
    }
    out << std::endl;
    row_num++;
  }
  return out;
}

std::vector<std::string> Room::splitString(std::string &string, char delimiter)
{
  std::vector<std::string> token;
  std::stringstream ss(string);
  std::string actual_token;
  while (getline(ss, actual_token, delimiter))
  {
    token.push_back(actual_token);
  }
  return token;
}

void Room::printEnemyStats()
{
  if (!allEnemiesDead())
    std::cout << "  ";
  int counter = 0;
  for (auto &c : enemies_)
  {
    if (c->getAliveStatus())
    {
      if (counter != 0)
      {
        std::cout << ",";
      }
      c->printStats();
      counter++;
    }
    else
    {
    }
  }
  std::cout << std::endl;
}

void Room::placePlayers(const std::vector<Player *> players, int room_change)
{
  players_ = players;
  int row = 0;
  int col = 0;
  if (room_change == 1)
  {
    std::pair<int, int> pos_entry = entry_point_->getPosition();
    row = pos_entry.first;
    col = pos_entry.second;
  }
  else
  {
    std::pair<int, int> pos_exit = exit_door_->getPosition();
    row = pos_exit.first;
    col = pos_exit.second;
  }
  for (auto &player : players)
  {
    if (player->getAliveStatus() == true)
    {
      collisionHandling(player, row, col);
    }
  }
}

void Room::collisionHandling(Entity *player, int row, int col)
{
  std::pair<int, int> target;
  target.first = -1;
  target.second = -1;
  int row_raw = row;
  int *row_ptr = &row_raw;
  int col_raw = col;
  int *col_ptr = &col_raw;
  for (int loop_count = 1; loop_count < std::max(width_, height_); loop_count++)
  {
    int starting_point = row - loop_count;
    *row_ptr = starting_point;
    for (int right = 0; right < loop_count; right++)
    {
      if (checkIfExistAndIsNullPtr(*row_ptr, *col_ptr))
      {
        if (target.first == -1 && target.second == -1)
        {
          target.first = *row_ptr;
          target.second = *col_ptr;
        }
      }
      moveRight(col_ptr);
    }
    for (int down = 0; down < (loop_count * 2); down++)
    {
      if (checkIfExistAndIsNullPtr(*row_ptr, *col_ptr))
      {
        if (target.first == -1 && target.second == -1)
        {
          target.first = *row_ptr;
          target.second = *col_ptr;
        }
      }
      moveDown(row_ptr);
    }
    for (int left = 0; left < (loop_count * 2); left++)
    {
      if (checkIfExistAndIsNullPtr(*row_ptr, *col_ptr))
      {
        if (target.first == -1 && target.second == -1)
        {
          target.first = *row_ptr;
          target.second = *col_ptr;
        }
      }
      moveLeft(col_ptr);
    }
    for (int up = 0; up < (loop_count * 2); up++)
    {
      if (checkIfExistAndIsNullPtr(*row_ptr, *col_ptr))
      {
        if (target.first == -1 && target.second == -1)
        {
          target.first = *row_ptr;
          target.second = *col_ptr;
        }
      }
      moveUp(row_ptr);
    }
    for (int right = 0; right <= loop_count - 1; right++)
    {
      if (checkIfExistAndIsNullPtr(*row_ptr, *col_ptr))
      {
        if (target.first == -1 && target.second == -1)
        {
          target.first = *row_ptr;
          target.second = *col_ptr;
        }
      }
      moveRight(col_ptr);
    }
  }
  fields_[target.first][target.second] = player;
  player->setPosition(target.first, target.second);
}

void Room::moveUp(int *row)
{
  --*row;
}

void Room::moveRight(int *col)
{
  ++*col;
}

void Room::moveLeft(int *col)
{
  --*col;
}

void Room::moveDown(int *row)
{
  ++*row;
}

void Room::setCompletion()
{
  completed_ = true;
}

int Room::getWidth()
{
  return width_;
}

int Room::getHeight()
{
  return height_;
}

bool Room::checkPosition(std::pair<int, int> pos)
{
  return (pos.first > 0 && pos.second > 0 && pos.first <= height_ && pos.second <= width_);
}

bool Room::makeDamage(std::pair<int, int> position, DamageType type, int damage)
{
  if (!checkPosition(position))
  {
    return false;
  }

  if (fields_[position.first - 1][position.second - 1] != nullptr)
  {
    fields_[position.first - 1][position.second - 1]->getDamage(type, damage);
    if (fields_[position.first - 1][position.second - 1]->getAliveStatus() == false)
    {
      if (fields_[position.first - 1][position.second - 1]->getEntityType() == EntityType::PLAYER)
      {
        Player *dead_player = dynamic_cast<Player *>(fields_[position.first - 1][position.second - 1]);
        Inventory *loot = dead_player->getDeathInventory();
        DeathLocation *new_death_location = new DeathLocation(loot);
        fields_[position.first - 1][position.second - 1] = new_death_location;
      }
      else if (fields_[position.first - 1][position.second - 1]->getEntityType() == EntityType::ENEMY)
      {
        Enemy *dead_enemy = dynamic_cast<Enemy *>(fields_[position.first - 1][position.second - 1]);
        if (dead_enemy->getAbbrev() != "L")
        {
          Inventory *loot = dead_enemy->getDeathInventory();
          DeathLocation *new_death_location = new DeathLocation(loot);
          enemies_.erase(std::remove(enemies_.begin(), enemies_.end(), dead_enemy), enemies_.end());
          delete dead_enemy;
          fields_[position.first - 1][position.second - 1] = new_death_location;
        }
        else
        {
          enemies_.erase(std::remove(enemies_.begin(), enemies_.end(), dead_enemy), enemies_.end());
          delete dead_enemy;
          fields_[position.first - 1][position.second - 1] = nullptr;
          lich_dead_ = 1;
        }
      }
    }
  }

  if (allEnemiesDead())
  {
    completed_ = true;
  }

  return 1;
}

bool Room::allEnemiesDead()
{
  if (enemies_.size() == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
  return true;
}

bool Room::allPlayersDead()
{
  for (Player *player : players_)
  {
    if (player->getAliveStatus() == true)
    {
      return false;
    }
  }
  return true;
}

bool Room::lichDead()
{
  return lich_dead_;
}

void Room::enemyValid(Enemy *enemy, int row, int col)
{
  if (checkIfExistAndIsNullPtr(row, col))
  {
    fields_[row][col] = enemy;
    enemy->setPosition(row, col);
    enemy->printMoveMessage();
    return;
  }
  else
  {
    collisionHandling(enemy, row, col);
    enemy->printMoveMessage();
    return;
  }
  std::cout << "hier bin ich" << std::endl;
  return;
}

void Room::enemyExecuteMove(Enemy *enemy, int row, int col, int target_number)
{
  int counter = 0;
  if (checkIfExist(row - 1 + 1, col + 1))
  {
    counter++;
    if (counter == target_number)
    {
      enemyValid(enemy, row - 1, col);
      return;
    }
  }
  if (checkIfExist(row - 1 + 1, col + 1 + 1))
  {
    counter++;
    if (counter == target_number)
    {
      enemyValid(enemy, row - 1, col + 1);
      return;
    }
  }
  if (checkIfExist(row + 1, col + 1 + 1))
  {
    counter++;
    if (counter == target_number)
    {
      enemyValid(enemy, row, col + 1);
      return;
    }
  }
  if (checkIfExist(row + 1 + 1, col + 1 + 1))
  {
    counter++;
    if (counter == target_number)
    {
      enemyValid(enemy, row + 1, col + 1);
      return;
    }
  }
  if (checkIfExist(row + 1 + 1, col + 1))
  {
    counter++;
    if (counter == target_number)
    {
      enemyValid(enemy, row + 1, col);
      return;
    }
  }
  if (checkIfExist(row + 1 + 1, col))
  {
    counter++;
    if (counter == target_number)
    {
      enemyValid(enemy, row + 1, col - 1);
      return;
    }
  }
  if (checkIfExist(row + 1, col - 1 + 1))
  {
    counter++;
    if (counter == target_number)
    {
      enemyValid(enemy, row, col - 1);
      return;
    }
  }
  if (checkIfExist(row, col - 1 + 1))
  {
    counter++;
    if (counter == target_number)
    {
      enemyValid(enemy, row - 1, col - 1);
      return;
    }
  }
}

void Room::enemyMove(Enemy *enemy)
{
  int adjacent_fields = enemyAdjacentFields(enemy);
  int target_number = Oop::Random::getInstance().getRandomNumber(adjacent_fields);
  std::pair<int, int> enemy_pos = enemy->getPosition();
  int col = enemy_pos.second;
  int row = enemy_pos.first;
  fields_[row][col] = nullptr;
  enemyExecuteMove(enemy, row, col, target_number);
}

int Room::enemyAdjacentFields(Enemy *enemy)
{
  std::pair<int, int> position = enemy->getPosition();
  int current_row = position.first;
  int current_col = position.second;
  int adjacent_fields = getNumberOfFields(current_row + 1, current_col + 1);
  return adjacent_fields;
}

int Room::getNumberOfFields(int row, int col)
{
  int amount = 0;
  if (checkIfExist(row - 1, col - 1))
  {
    amount = amount + 1;
  }
  if (checkIfExist(row - 1, col))
  {
    amount = amount + 1;
  }
  if (checkIfExist(row - 1, col + 1))
  {
    amount = amount + 1;
  }
  if (checkIfExist(row, col - 1))
  {
    amount = amount + 1;
  }
  if (checkIfExist(row, col + 1))
  {
    amount = amount + 1;
  }
  if (checkIfExist(row + 1, col - 1))
  {
    amount = amount + 1;
  }
  if (checkIfExist(row + 1, col))
  {
    amount = amount + 1;
  }
  if (checkIfExist(row + 1, col + 1))
  {
    amount = amount + 1;
  }
  return amount;
}

// A1 OOP Jesenko
///
bool Room::checkIfExist(int row, int col)
{
  unsigned long int row_num = row;
  unsigned long int col_num = col;
  if (((row_num - 1) >= 0 && (row_num - 1) < fields_.size()) && ((col_num - 1) >= 0 && (col_num - 1) < fields_[0].size()))
  {
    return true;
  }
  return false;
}
///
bool Room::checkIfExistAndIsNullPtr(int row, int col)
{
  int target_row = row + 1;
  int target_col = col + 1;
  if (checkIfExist(target_row, target_col))
  {
    if (fields_[row][col] == nullptr)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
  return false;
}

bool Room::checkIfExistAndIsInSet(std::set<Player *> player, int row, int col, Player *&ans)
{
  int target_row = row + 1;
  int target_col = col + 1;
  if (checkIfExist(target_row, target_col))
  {
    for (auto &p : player)
    {
      if (fields_[row][col] == p)
      {
        ans = p;
        return true;
      }
    }
  }
  else
  {
    return false;
  }
  return false;
}

int Room::moveExecute(Player *player, int target_row, int target_col, Story *story)
// -2 if unsuccessfull, -1 if successfull, room_id if it is a Door
{
  std::pair<int, int> position = player->getPosition();
  int current_row = position.first;
  int current_col = position.second;
  if (current_row == target_row && (current_col == target_col + 1 || current_col == target_col - 1))
  {
    if (fields_[target_row][target_col] == nullptr)
    {
      fields_[target_row][target_col] = player;
      fields_[current_row][current_col] = nullptr;
      player->setPosition(target_row, target_col);
      player->printMoveMessage();
      return -1;
    }
    else if (fields_[target_row][target_col] != nullptr &&
             fields_[target_row][target_col]->getAbbrev().compare("D") == 0)
    {
      Door *door = dynamic_cast<Door *>(fields_[target_row][target_col]);
      if (door->isDoorLocked() == true)
      {
        story->printStory("E_MOVE_LOCKED_DOOR");
        return -2;
      }
      else
      {
        fields_[current_row][current_col] = nullptr;
        player->setPosition(target_row, target_col);
        player->printMoveMessage();
        player->setPosition(current_row, current_col);
        deletePlayers();
        return door->connectedTo();
      }
    }
    else
    {
      story->printStory("E_INVALID_POSITION");
      return -2;
    }
  }
  else if ((current_row == target_row + 1 || target_row - 1 == current_row) && 
           (target_col + 1 == current_col || target_col == current_col || target_col - 1 == current_col))
  {
    if (fields_[target_row][target_col] == nullptr)
    {
      fields_[target_row][target_col] = player;
      fields_[current_row][current_col] = nullptr;
      player->setPosition(target_row, target_col);
      player->printMoveMessage();
      return -1;
    }
    else if (fields_[target_row][target_col] != nullptr &&
             fields_[target_row][target_col]->getAbbrev().compare("D") == 0)
    {
      Door *door = dynamic_cast<Door *>(fields_[target_row][target_col]);
      if (door->isDoorLocked() == true)
      {
        story->printStory("E_MOVE_LOCKED_DOOR");
        return -2;
      }
      else
      {
        fields_[current_row][current_col] = nullptr;
        player->setPosition(target_row, target_col);
        player->printMoveMessage();
        player->setPosition(current_row, current_col);
        deletePlayers();
        return door->connectedTo();
      }
    }
    else
    {
      story->printStory("E_INVALID_POSITION");
      return -2;
    }
  }
  else
  {
    story->printStory("E_INVALID_POSITION");
    return -2;
  }
  return -2;
}

void Room::deletePlayers()
{
  for (auto &c : players_)
  {
    if (c->getAliveStatus() == true)
    {
      std::pair<int, int> pos = c->getPosition();
      c->setResistance(DamageType::NONE);
      int row = pos.first;
      int col = pos.second;
      fields_[row][col] = nullptr;
    }
  }
  players_.clear();
}

void Room::deleteEnemies()
{
  for (auto &c : enemies_)
  {
    std::pair<int, int> pos = c->getPosition();
    int row = pos.first;
    int col = pos.second;
    fields_[row][col] = nullptr;
    delete c;
  }
}

bool Room::notEntered()
{
  return first_entry_;
}

void Room::setEntered()
{
  first_entry_ = 1;
}

std::vector<Enemy *> Room::getEnemies()
{
  return enemies_;
}

std::set<std::string> Room::getEnemyTypes()
{
  std::set<std::string> s;
  for (auto &enemy : enemies_)
  {
    s.insert(enemy->getAbbrev());
  }
  return s;
}

Player *Room::chosePlayerForAttack(Enemy *enemy)
{
  int dist = 1000000000;
  int health = 1000000000;
  Player *res = nullptr;
  std::set<Player *> additional_check;
  for (auto &player : players_)
  {
    if (player->getAliveStatus() == false)
      continue;
    int new_dist = abs(enemy->getPosition().first - player->getPosition().first) + 
                   abs(enemy->getPosition().second - player->getPosition().second);
    int new_health = player->getHealth();
    if (dist == new_dist && health == new_health)
    {
      additional_check.insert(player);
      additional_check.insert(res);
    }
    else if (new_dist < dist || (new_dist == dist && new_health < health))
    {
      health = new_health;
      dist = new_dist;
      res = player;
    }
  }
  if (!additional_check.empty())
  {
    res = findNearest(additional_check, enemy->getPosition().first, enemy->getPosition().second);
  }
  return res;
}

// mostly copypasted from collisionHandlig by julia
Player *Room::findNearest(std::set<Player *> player, int row, int col)
{
  std::pair<int, int> target;
  target.first = -1;
  target.second = -1;
  int row_raw = row;
  int *row_ptr = &row_raw;
  int col_raw = col;
  int *col_ptr = &col_raw;
  Player *ans = nullptr;
  for (int loop_count = 1; std::max(width_, height_); loop_count++)
  {
    int starting_point = row - loop_count;
    *row_ptr = starting_point;
    for (int right = 0; right < loop_count; right++)
    {
      // std::cout << "current col" << *col_ptr << std::endl;
      if (checkIfExistAndIsInSet(player, *row_ptr, *col_ptr, ans))
      {
        return ans;
      }
      moveRight(col_ptr);
    }
    for (int down = 0; down < (loop_count * 2); down++)
    {
      if (checkIfExistAndIsInSet(player, *row_ptr, *col_ptr, ans))
      {
        return ans;
      }
      moveDown(row_ptr);
    }
    for (int left = 0; left < (loop_count * 2); left++)
    {
      if (checkIfExistAndIsInSet(player, *row_ptr, *col_ptr, ans))
      {
        return ans;
      }
      moveLeft(col_ptr);
    }
    for (int up = 0; up < (loop_count * 2); up++)
    {
      if (checkIfExistAndIsInSet(player, *row_ptr, *col_ptr, ans))
      {
        return ans;
      }
      moveUp(row_ptr);
    }
    for (int right = 0; right <= loop_count - 1; right++)
    {
      if (checkIfExistAndIsInSet(player, *row_ptr, *col_ptr, ans))
      {
        return ans;
      }
      moveRight(col_ptr);
    }
  }
  return nullptr;
}

void Room::enemyPhase()
{
  for (auto &enemy : enemies_)
  {
    if (enemy->getAliveStatus() == false)
    {
    }
    else
    {
      Player *player = chosePlayerForAttack(enemy);
      if (!attack(player, enemy))
      {
        enemyMove(enemy);
      }
      if (allPlayersDead())
      {
        return;
      }
    }
  }
}

Room::~Room()
{
  for (auto &p : players_)
  {
    if (p != nullptr && p->getAliveStatus() == true)
    {
      auto pos = p->getPosition();
      fields_[pos.first][pos.second] = nullptr;
    }
  }
  for (auto &c : fields_)
  {
    for (auto &test : c)
    {
      if (test != nullptr)
      {
        delete test;
      }
    }
  }
}

std::vector<Weapon *> Room::getToChoose(Enemy *enemy, bool can_melee, ItemsList *items_list)
{
  std::vector<Weapon *> choose_from;
  if (enemy->getType() == CharacterType::ZOMBIE)
  {
    if (can_melee)
      choose_from.push_back(items_list->getWeaponItemPtr("DAGG", 0));
  }
  if (enemy->getType() == CharacterType::GOBLIN)
  {
    if (can_melee)
      choose_from.push_back(items_list->getWeaponItemPtr("HAXE", 0));
    choose_from.push_back(items_list->getWeaponItemPtr("SBOW", 0));
  }
  if (enemy->getType() == CharacterType::LICH)
  {

    choose_from.push_back(items_list->getWeaponItemPtr("QFIR", 1));
    if (can_melee)
      choose_from.push_back(items_list->getWeaponItemPtr("QCLD", 1));
    choose_from.push_back(items_list->getWeaponItemPtr("QACD", 1));
    if (can_melee)
      choose_from.push_back(items_list->getWeaponItemPtr("QFRC", 1));
  }
  return choose_from;
}

int Room::getNumber()
{
  return room_id_;
}

bool Room::compareId(Enemy *e1, Enemy *e2)
{
  return (e1->getId() < e2->getId());
}

void Room::unlockDoors()
{
  for (auto &c : fields_)
  {
    for (auto &element : c)
    {
      if (element != nullptr && element->getAbbrev().compare("D") == 0)
      {
        Door *door = dynamic_cast<Door *>(element);
        door->openDoor();
      }
    }
  }
}

std::vector<std::vector<Entity *>> &Room::getFields()
{
  return fields_;
}

std::vector<std::pair<int, int>> Room::getAttackPositions(Weapon *weapon, std::pair<int, int> player_position,
                                                    Player *player, Enemy *enemy)
{
  std::vector<std::pair<int, int>> positions;
  if (weapon->getDamagePattern() == DamagePattern::HIT)
  {
    if (checkPosition(player_position))
      positions.push_back(player_position);
  }

  ////////////////////////////////////////////////////////////////////////

  if (weapon->getDamagePattern() == DamagePattern::LINE)
  {
    std::pair<int, int> delta = std::make_pair(player->getPosition().first - enemy->getPosition().first,
                                               player->getPosition().second - enemy->getPosition().second);
    std::pair<int, int> position2 = player_position;
    while (checkPosition(position2))
    {
      positions.push_back(position2);
      position2.first += delta.first;
      position2.second += delta.second;
    }
  }

  //////////////////////////////////////////////////////////////////////

  if (weapon->getDamagePattern() == DamagePattern::SHOT)
  {
    if (checkPosition(player_position))
      positions.push_back(player_position);
  }

  /////////////////////////////////////////////////////////////////////

  if (weapon->getDamagePattern() == DamagePattern::BURST)
  {
    auto position = player_position;
    if (checkPosition(position))
      positions.push_back(position);
    position.second++;
    if (checkPosition(position))
      positions.push_back(position);
    position.second -= 2;
    if (checkPosition(position))
      positions.push_back(position);
    position.second++;
    position.first++;
    if (checkPosition(position))
      positions.push_back(position);
    position.first -= 2;
    if (checkPosition(position))
      positions.push_back(position);
    position.first++;
  }
  return positions;
}

bool Room::attack(Player *player, Enemy *enemy)
{
  ItemsList *items_list = new ItemsList();
  std::pair<int, int> player_position = player->getPosition();
  bool can_melee = 1;
  if (abs(player_position.first - enemy->getPosition().first) > 1 || 
      abs(player_position.second - enemy->getPosition().second) > 1) 
    can_melee = 0;
  std::vector<Weapon *> choose_from = getToChoose(enemy, can_melee, items_list);
  if (choose_from.size() == 0)
  {
    delete items_list;
    return 0;
  }
  int pos = Oop::Random::getInstance().getRandomNumber((int)choose_from.size());
  Weapon *weapon = choose_from.at(pos - 1);
  std::cout << '\n'
            << enemy->getName() << " [" << enemy->getAbbrev() << enemy->getId() << "] used \""
            << weapon->getName() << "\" on (" << player->getPosition().first + 1 << "," 
            << player->getPosition().second + 1 << ") affecting";
  std::vector<std::pair<int, int>> positions;
  player_position.first++;
  player_position.second++;
  positions = getAttackPositions(weapon, player_position, player, enemy);
  std::sort(positions.begin(), positions.end());
  for (int i = 0; i < (int)positions.size(); i++)
  {
    auto p = positions[i];
    std::cout << " (" << p.first << ',' << p.second << ")";
    if (i != (int)positions.size() - 1)
      std::cout << ",";
    else
      std::cout << ".";
  }
  std::cout << '\n';
  int damage = diceRoll(weapon->getRollAmount(), weapon->getDiceType());
  std::string abrev = weapon->getAbbreviation();
  if (abrev == "DAGG" || abrev == "SBOW")
  {
    damage += enemy->getVitality();
  }
  if (abrev == "HAXE")
  {
    damage += enemy->getStrength();
  }
  for (auto &p : positions)
  {
    makeDamage(p, weapon->getDamageType(), damage);
    if (allPlayersDead() || lichDead())
    {
      break;
    }
  }
  delete items_list;
  return 1;
}