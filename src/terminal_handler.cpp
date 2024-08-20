#include "../include/terminal_handler.h"

struct termios TerminalHandler::original_termios;

void TerminalHandler::set_new_terminal_configuration() {
  signal(SIGINT, TerminalHandler::handle_signal);
  tcgetattr(STDIN_FILENO, &original_termios);
  struct termios raw = original_termios;
  raw.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void TerminalHandler::reset_terminal_configuration() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}

void TerminalHandler::handle_signal(int signal) {
    reset_terminal_configuration();
    exit(signal);
}
