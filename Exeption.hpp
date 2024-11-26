//---------------------------------------------------------------------------------------------------------------------
//
// custom exception class for throwing errors during the execution of commands
//
// Group: 090
//
// Author: Maryia Filipovich 12328063
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef EXEPTION_HPP
#define EXEPTION_HPP
#include <string>
#include "Game.hpp"
#include <exception>


class Exception : public std::exception
{
private:
  std::string error_key;
  Game* game_;
public:
  //---------------------------------------------------------------------------------------------------------------------
  ///
  /// constructor for exception, that sets its attributes
  ///
  ///
  /// @return constructed Exception
  //
  Exception(const std::string& key, Game* game) : error_key(key), game_(game) {}
  //---------------------------------------------------------------------------------------------------------------------
  ///
  /// copy constructor is default
  ///
  //
  Exception(const Exception&) = default;
  //---------------------------------------------------------------------------------------------------------------------
  ///
  /// default destuctor for exception
  ///
  //
  ~Exception() = default;
  //---------------------------------------------------------------------------------------------------------------------
  ///
  /// method that prints the error-message corresponding to error type
  ///
  ///
  /// @return nullptr because we don't need anything to return
  //
  virtual const char* what() const noexcept override
  {
    game_->writeStory(error_key);
    return nullptr;
  }
};

#endif