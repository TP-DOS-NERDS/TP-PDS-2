#include "../../include/games/snake.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <conio.h>

Snake::Snake(Player p) : player(p), length(4), direction(77) {
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

    // Start
    for (int i = 0; i < length; ++i) {
        snake[0][i] = 1;
        snake[1][i] = i + 1;
        board[1][i + 1] = '*';  // Snake body
    }
    board[1][4] = '@';  // Snake head
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
    system("cls");
    for (int i = 0; i < 22; ++i) {
        for (int j = 0; j < 22; ++j) {
            std::cout << board[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

bool Snake::move_snake(int dx, int dy) {
    int new_x = snake[0][length - 1] + dx;
    int new_y = snake[1][length - 1] + dy;

    if (is_game_over(new_x, new_y)) {
        return false;
    }

    if (board[new_x][new_y] == '$') { // Food (or points)
        length++;
        player.increase_wins();
        place_food();
    } else {
        // Remove snake body
        board[snake[0][0]][snake[1][0]] = ' ';
        for (int i = 0; i < length - 1; ++i) {
            snake[0][i] = snake[0][i + 1];
            snake[1][i] = snake[1][i + 1];
        }
    }

    // Update snake head
    snake[0][length - 1] = new_x;
    snake[1][length - 1] = new_y;

    // New snake head
    board[new_x][new_y] = '@';

    // New snake body
    for (int i = 0; i < length - 1; ++i) {
        board[snake[0][i]][snake[1][i]] = '*';
    }

    print_board();
    return true;
}

bool Snake::is_game_over(int x, int y) const {
    return (x == 0 || x == 21 || y == 0 || y == 21 || board[x][y] == '*');
}

void Snake::move() {
    int dx = 0, dy = 0;
    switch (direction) {
        case 72: dx = -1; dy = 0; break; // Up
        case 80: dx = 1; dy = 0; break;  // Down
        case 75: dx = 0; dy = -1; break; // Left
        case 77: dx = 0; dy = 1; break;  // Right
    }

    if (!move_snake(dx, dy)) {
        // Display game over message
        std::cout << "Game Over! " << player.get_username() << " perdeu!" << std::endl;
        Sleep(2000); 
    }
}

void Snake::change_direction(int new_direction) {
    direction = new_direction;
}

bool Snake::is_game_over() const {
    return length == 0;
}