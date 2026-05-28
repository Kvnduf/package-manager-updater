#ifndef PACMAN_EXECUTOR_H
#define PACMAN_EXECUTOR_H

#include "pacman.h"

typedef struct 
{
    void (*on_pacman_found_and_start_execution)(const char* pacman_name);
    void (*on_pacman_not_found)();
    void (*on_command_exec)(const pacman_command_t command);
    void (*on_command_execution_error)(const int error_code);
    void (*on_command_execution_success)(void);
}pacman_executor_feedback_t ;


int pacmans_execute(pacman_t pacman[], size_t nb_pacmans, const pacman_executor_feedback_t* feedback);

#endif
