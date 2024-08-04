#ifndef FORBIDDEN_ACTION_EXCEPTION_H
#define FORBIDDEN_ACTION_EXCEPTION_H

#include <exception>

enum class ErrorMessage { player_id_already_taken, player_not_found };

class forbidden_action_exception : public std::exception{
private:
  ErrorMessage error_message;  

public:
  forbidden_action_exception(ErrorMessage error_message) {
    this->error_message = error_message;
  }
};

#endif
