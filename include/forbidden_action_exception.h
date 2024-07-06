#ifndef FORBIDDEN_ACTION_EXCEPTION_H
#define FORBIDDEN_ACTION_EXCEPTION_H

#include <exception>

enum message { unique_identifier_taken, entity_not_found };

class forbidden_action_exception : public std::exception{
private:
  message error_message;  

public:
  forbidden_action_exception(message error_message) {
    this->error_message = error_message;
  }
};

#endif
