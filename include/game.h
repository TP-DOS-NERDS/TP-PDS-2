#ifndef GAME2_H
#define GAME2_H

#include <utility>

class Game {
public:
  virtual void play() = 0;

private:
  virtual bool is_position_valid(std::pair<int,int> position) = 0;
  virtual bool game_ended() = 0;
  virtual void play_round() = 0;
};

#endif
