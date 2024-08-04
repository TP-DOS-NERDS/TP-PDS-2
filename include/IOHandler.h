#ifndef IOHandler_H
#define IOHandler_H

#include "player.h"
#include "game_ids.h"
#include <iostream>
#include <vector>
#include <string>

namespace IOHandler {
  template <typename T>
  T get();

  template <typename T>
  void print(const T& value);

  template <typename T>
  void print(const Player& player);

  template <typename T>
  void print(const std::vector<const Player*>& players);
}

#include "../src/IOHandler.cpp"

#endif

