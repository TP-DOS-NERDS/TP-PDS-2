#include "../include/player.h"
#include "../include/games/snake.h"

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h> 

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

int main() {
    set_terminal_mode(true);

    Player player("azyury", "Yuri");
    Snake game(player);

    std::cout << " -- FASE DE TESTES [INTERFACE E MENU A SEREM FEITOS] -- " << std::endl;
    std::cout << "Use as setas para mover a cobra. Pressione 'q' para sair." << std::endl;

    bool running = true;
    while (running) {
        if (kbhit()) { 
            int key = get_key();
            
            if (key != EOF) { 
                switch (key) {
                    case 0: 
                        game.change_direction(0);
                        break;
                    case 1: 
                        game.change_direction(1);
                        break;
                    case 2: 
                        game.change_direction(2);
                        break;
                    case 3: 
                        game.change_direction(3);
                        break;
                    case 'q': 
                        std::cout << "Saindo do jogo" << std::endl; 
                        running = false;
                        break;
                    default:
                        std::cout << "Tecla não reconhecida: " << key << std::endl; 
                        break;
                }
            }
        }

        if (!game.is_game_over()) {
            game.move(); 
        }
        usleep(100000); 
    }

    set_terminal_mode(false); 
    return 0;
}
