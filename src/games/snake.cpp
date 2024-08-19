#include "../../include/games/snake.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

Snake::Snake(Player p) : player(p), length(4), direction(3), score(0) {
    init_board();
    place_food();
}

void Snake::init_board() {
    for (int i = 0; i < 22; ++i) {
        for (int j = 0; j < 22; ++j) {
            if (i == 0 || i == 21 || j == 0 || j == 21) {
                board[i][j] = '#';
            } else {
                board[i][j] = ' ';
            }
        }
    }

    for (int i = 0; i < length; ++i) {
        snake[0][i] = 1;
        snake[1][i] = i + 1;
        board[1][i + 1] = '*'; 
    }
    board[1][4] = '@'; 
}

void Snake::place_food() {
    srand(static_cast<unsigned>(time(0)));
    do {
        food_x = rand() % 20 + 1;
        food_y = rand() % 20 + 1;
    } while (board[food_x][food_y] != ' ');
    board[food_x][food_y] = '$';
}

void Snake::print_board() const {
    system("clear"); 
    std::cout << "Score: " << score << "\n"; 
    for (int i = 0; i < 22; ++i) {
        for (int j = 0; j < 22; ++j) {
            std::cout << board[i][j] << ' '; 
        }
        std::cout << '\n';
    }
}

bool Snake::move_snake(int dx, int dy) {
    int new_x = snake[0][length - 1] + dx;
    int new_y = snake[1][length - 1] + dy;

    if (is_game_over(new_x, new_y)) {
        return false;
    }

    if (board[new_x][new_y] == '$') { 
        length++;
        score++;
        place_food();
    } else {
        board[snake[0][0]][snake[1][0]] = ' ';
        for (int i = 0; i < length - 1; ++i) {
            snake[0][i] = snake[0][i + 1];
            snake[1][i] = snake[1][i + 1];
        }
    }

    snake[0][length - 1] = new_x;
    snake[1][length - 1] = new_y;

    board[new_x][new_y] = '@';

    for (int i = 0; i < length - 1; ++i) {
        board[snake[0][i]][snake[1][i]] = '*';
    }

    print_board();

    if (is_board_full()) {
        std::cout << "Parabens, " << player.get_username() << " venceu!\n";
        player.increase_wins();
        sleep(2);
        return false;
    }

    return true;
}

bool Snake::is_board_full() const {
    for (int i = 1; i < 21; ++i) {
        for (int j = 1; j < 21; ++j) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

bool Snake::is_game_over(int x, int y) const {
    return (x == 0 || x == 21 || y == 0 || y == 21 || board[x][y] == '*');
}

void Snake::move() {
    int dx = 0, dy = 0;

    switch (direction) {
        case 0: dx = -1; dy = 0; break; // Up
        case 1: dx = 1; dy = 0; break;  // Down
        case 2: dx = 0; dy = -1; break; // Left
        case 3: dx = 0; dy = 1; break;  // Right
    }

    if (!move_snake(dx, dy)) {
        std::cout << "Game Over! " << player.get_username() << " perdeu!\n";
        player.increase_defeats();
        sleep(2);
        length = 0; 
    }
}

bool Snake::is_game_over() const {
    return length == 0;
}

Snake::~Snake() {
    
}

void Snake::change_direction(int new_direction) {
    if ((direction == 0 && new_direction != 1) ||
        (direction == 1 && new_direction != 0) ||
        (direction == 2 && new_direction != 3) ||
        (direction == 3 && new_direction != 2)) {
        direction = new_direction;
    }
}

void Snake::wait(int milliseconds) {
    usleep(milliseconds * 1000);
}

int Snake::get_score() const {
    return score;
}
