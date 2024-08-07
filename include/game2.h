#ifndef GAME2_H
#define GAME2_H

class Game2 {
public:
  Game2();
  virtual bool game_ended() = 0;
  virtual void play();

private:
  virtual void play_round() = 0;
};

#endif
