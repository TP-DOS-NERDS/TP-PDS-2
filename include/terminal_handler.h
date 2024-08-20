#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <csignal>


class TerminalHandler {
public:
  static void set_new_terminal_configuration();
  static void reset_terminal_configuration();

private:
  static struct termios original_termios;
  static void handle_signal(int signal);
};