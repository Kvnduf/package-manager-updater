#include "pacman_executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>

#define SECURE_CALL(fmt, ...) if (fmt) {fmt(__VA_ARGS__);}

static pacman_executor_feedback_t default_feedback = {
    NULL, NULL, NULL, NULL, NULL
};

static int execute_command(const char *command) {
    if (!command || command[0] == '\0')  return -1;
    int res = system(command);
    if (res == -1) return -1;
    if (!WIFEXITED(res))  return -1;

    return WEXITSTATUS(res);
}

static int pacman_check_existence(pacman_t* pacman) {
    if (!pacman) return -1;
    char check_command[PACMAN_MAX_LINE_LENGTH];
    int n = snprintf(check_command, sizeof(check_command), "command -v %s > /dev/null 2>&1", pacman->nameCmd);
    if (n < 0 || (size_t)n >= sizeof(check_command)) return -1;
    return execute_command(check_command) == 0 ? 0 : 1;
}


static int pacman_execute_command(pacman_t* pacman, pacman_command_t command, const pacman_executor_feedback_t* feedback) {
    if (!pacman) return -1;
    SECURE_CALL(feedback->on_command_exec, command);
    int res = execute_command(pacman->commands[command]);
    if (res != 0) {
        SECURE_CALL(feedback->on_command_execution_error, res);
        return 1;
    }
    SECURE_CALL(feedback->on_command_execution_success);
    return 0;
}

static int pacman_execute(pacman_t* pacman, const pacman_executor_feedback_t* feedback) {
    if (!pacman) return -1;
    SECURE_CALL(feedback->on_pacman_found_and_start_execution, pacman->name);
    if (pacman_check_existence(pacman) != 0) {
        SECURE_CALL(feedback->on_pacman_not_found);
        return 1;
    }
    int res;

    /* UPDATE */
    res = pacman_execute_command(pacman, PACMAN_UPGRADE_CMD, feedback);
    if (res == -1) return res;

    /* CLEAN ORPHANS */
    res = pacman_execute_command(pacman, PACMAN_CLEAN_ORPHANS_CMD, feedback);
    if (res == -1) return res;

    /* CLEAN CACHE */
    res = pacman_execute_command(pacman, PACMAN_CLEAN_CACHE_CMD, feedback);
    if (res == -1) return res;
    return 0;

}

int pacmans_execute(pacman_t pacman[], size_t nb_pacmans, const pacman_executor_feedback_t* feedback) {
    if (!pacman || nb_pacmans == 0) return -1;
    if (!feedback) feedback = &default_feedback;
    bool had_nonfatal_failure = false;
    for (size_t i = 0; i < nb_pacmans; i++) {
        int res = pacman_execute(&pacman[i], feedback);
        if (res == -1) return -1;
        if (res != 0) had_nonfatal_failure = true;
    }
    return had_nonfatal_failure ? 1 : 0;
}
