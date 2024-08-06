#include "../include/player.h"
#include "../include/games/snake.h"

#include <iostream>
#include <windows.h>
#include <conio.h>

// Código provisório para testar as funcionalidades básicas.
// Posteriormente, faremos um menu e outros extras.
int main() {
    Player player("azyury", "Yuri");
    Snake game(player);

    std::cout << " -- FASE DE TESTES [INTERFACE E MENU A SEREM FEITOS] -- " << std::endl;
    
    bool running = true;
    while (running) {
        if (_kbhit()) {
            int key = _getch();
            switch (key) {
                case 72: // Up
                case 80: // Down
                case 75: // Left
                case 77: // Right
                    game.change_direction(key);
                    break;
                case 'q': // Quit game
                    running = false;
                    break;
            }
        }

        if (!game.is_game_over()) {
            game.move();
            Sleep(100); // Interval between each movement
        }
    }

    return 0;
}
