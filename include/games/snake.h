#ifndef SNAKE_H
#define SNAKE_H

#include <string>
#include "../player.h"

class Snake {
private:
    Player player;
    char board[22][22];
    int snake[2][100];  // Snake coordinates
    int length; // Snake size
    int direction; // Snake direction
    int food_x, food_y;
    int score;

    void init_board();
    void place_food();
    void print_board() const;
    bool move_snake(int dx, int dy);
    bool is_game_over(int x, int y) const;
    bool is_board_full() const;

public:
    Snake(Player player);
    ~Snake();

    void move();
    void change_direction(int new_direction);
    bool is_game_over() const;
    void wait(int milliseconds);
    int get_score() const;
};

#endif
