//---------------------------------------------------------------------------------------------------------------------
// Door.hpp
//
// This is a header file for the door class, which is derived from the entity class.
//
// Group: 090
//
// Author: Julia Jesenko, 12312254
//---------------------------------------------------------------------------------------------------------------------
//
#ifndef DOOR_HPP
#define DOOR_HPP

#include <iostream>
#include <vector>
#include <utility>
#include "Entity.hpp"

class Door : public Entity
{
  private:
  bool is_locked_;
  int connection_to_;

  public:
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The constructor of the door class, sets the members with the correct values.
    ///
    /// @param connection_to room id of the room where the door leads to
    /// @param row row positionnumber
    /// @param col column position number
    //
    Door(int connection_to, int row, int col)
    {
      is_locked_ = true;
      connection_to_ = connection_to;
      position_ = std::pair<int,int> (row,col);
      abbreviation_ = "D";
    }
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// We do not allow initializing one door object to another one.
    //
    Door(const Door& door) = delete;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The destructor is set to default.
    //
    ~Door() = default;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the is locked member
    ///
    /// @param -
    ///
    /// @return the value of the is_locked member
    //
    bool isDoorLocked()
    {
      return is_locked_;
    }
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the connected to member
    ///
    /// @param -
    ///
    /// @return the value of the connection_to member
    //
    int connectedTo()
    {
      return connection_to_;
    }
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function prints the door symbol, with the connection to number
    ///
    /// @param -
    ///
    /// @return nothing
    //
    void print() const override
    {
      if(is_locked_ == true)
      {
        std::cout << "#D" << connection_to_;
      }
      else
      {
        std::cout << " D" << connection_to_;
      }
    }
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the position
    ///
    /// @param none
    ///
    /// @return the position member
    //
    std::pair<int,int> getPosition() override
    {
      return position_;
    }
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the abbreviation member
    ///
    /// @param none
    ///
    /// @return the abbreviation member
    //
    std::string getAbbrev() override
    {
      return abbreviation_;
    }
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The function changes the value of the is_locked member to false.
    ///
    /// @param none
    ///
    /// @return nothing
    //
    void openDoor()
    {
      is_locked_ = false;
    }
};

#endif