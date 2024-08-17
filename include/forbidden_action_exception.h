#ifndef FORBIDDEN_ACTION_EXCEPTION_H
#define FORBIDDEN_ACTION_EXCEPTION_H

#include <exception>

enum class ErrorMessage { player_id_already_taken, player_not_found, game_not_found, invalid_player_sorting_criterion, command_not_found };

class forbidden_action_exception : public std::exception{
public:
  ErrorMessage error_message;  

  forbidden_action_exception(ErrorMessage error_message) {
    this->error_message = error_message;
  }
};

#endif
