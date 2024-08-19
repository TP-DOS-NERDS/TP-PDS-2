#include "../../include/games/snake.h"
#include "../../include/player.h"

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h> 

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

Snake::Snake(Player p) : player(p), length(4), direction(3), score(0) {
    init_board();
    place_food();
}

Snake::Snake(): player(Player("placeholder1", "placeholder1")), length(4), direction(3), score(0) {
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
  std::cout << '\n';
}

bool Snake::move_snake(int dx, int dy) {
  int new_x = snake[0][length - 1] + dx;
  int new_y = snake[1][length - 1] + dy;

  if (is_game_over(new_x, new_y)) {
    return false;
  }

  if (board[new_x][new_y] == '$') { // Food (or points)
    length++;
//    player.increase_wins(GameId::snake);
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
    this->running=false;
    player.increase_defeats(GameId::snake);
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

// unused
bool Snake::is_position_valid(std::pair<int,int> position) {
  return true;
}

bool Snake::game_ended() {
  return this->is_game_over();
}

void Snake::play_round() {
  this->play();
}

void set_terminal_mode(bool enable) {
  static struct termios oldt, newt;
  if (enable) {
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  } else {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  }
}

int get_key() {
  int ch = getchar();
  if (ch == 27) { // Esc
    getchar(); 
    switch (getchar()) {
      case 'A': return 0; // Up
      case 'B': return 1; // Down
      case 'C': return 3; // Right
      case 'D': return 2; // Left
    }
  }
  return ch;
}

bool kbhit() {
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF) {
    ungetc(ch, stdin);
    return true;
  }

  return false;
}

void Snake::play() {
  this->running = true; 
  while (running) {
    if (kbhit()) {
      int key = get_key();
      if (key != EOF) { 
        switch (key) {
          case 0: 
          case 1:
          case 2:
          case 3:
            this->change_direction(key);
            break;
          default:
            break;
        }
      }
    }

    if (!this->is_game_over()) {
      this->move(); 
    }
    std::cout << 2 << std::endl;
    usleep(100000); 
  }

  std::cout << 1 << std::endl;
  set_terminal_mode(false);
}

// single player. then, if there is a winner, it has to be one
int Snake::get_winner() {
  return 1;
}

int Snake::get_score() const {
    return score;
}