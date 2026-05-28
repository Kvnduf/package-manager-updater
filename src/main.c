#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include "config.h"
#include "pacman_executor.h"
#include "utils.h"
#include "pacman_reader.h"
#include <stdbool.h>


/* Define feedback functions for pacman_executor */

#define RESET   "\x1b[0m"

#define WHITE   "\x1b[37m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define CYAN    "\x1b[36m"
#define MAGENTA "\x1b[35m"
#define AQUA    "\x1b[36m"

#define BOLD    "\x1b[1m"


void on_pacman_found_and_start_execution(const char* pacman_name) {
    struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    int n = (w.ws_col - 16 - (int)strlen(pacman_name)) / 2 - 1;
    printf(AQUA BOLD "\n");
    for (int i = 0; i < n; i++) printf("=");
    printf(WHITE " [ Updating : %s ] " AQUA, pacman_name);
    for (int i = 0; i < n; i++) printf("=");
    
    printf("\n\n"RESET);
}

void on_pacman_not_found() {
    printf(
        RED BOLD
        "[✗] Package manager not found\n"
        RESET
    );
}

void on_command_exec(const pacman_command_t command) {
    const char* command_name = NULL;
    switch (command) {
        case PACMAN_UPGRADE_CMD:
            command_name = "Upgrade";
            break;
        case PACMAN_CLEAN_ORPHANS_CMD:
            command_name = "Clean Orphans";
            break;
        case PACMAN_CLEAN_CACHE_CMD:
            command_name = "Clean Cache";
            break;
        default:
            command_name = "Unknown Command";
    }
    printf(
        YELLOW BOLD
        "[➜] %s"
        RESET
        "\n\n",
        command_name
    );
}

void on_command_execution_error(const int error_code) {
    printf(
        RED BOLD
        "[✗] Command execution failed :"
        YELLOW " %d\n\n"
        RESET,
        error_code
    );
}

void on_command_execution_success(void) {
    printf(
        GREEN BOLD
        "[✓] Command executed successfully\n\n"
        RESET
    );
}

pacman_executor_feedback_t feedback = {
        .on_pacman_found_and_start_execution = on_pacman_found_and_start_execution,
        .on_pacman_not_found = on_pacman_not_found,
        .on_command_exec = on_command_exec,
        .on_command_execution_error = on_command_execution_error,
        .on_command_execution_success = on_command_execution_success
    };

/* Main function */



void print_help(const char* program_name) {
    printf("Usage : %s [OPTIONS]\n", program_name);
    printf("  -l, --list       Display packages manager list\n");
    printf("  -p, --poweroff   Shutdown the system after execution\n");
    printf("  -h, --help       Display help information\n");
}

int main(int argc, char *argv[]) {
    int opt;

    
    bool poweroff = false;
    bool list = false;
    bool help = false;
    bool execute = true;

    static struct option long_options[] = {
        {"list",     no_argument, 0, 'l'},
        {"poweroff", no_argument, 0, 'p'},
        {"help",     no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "lph", long_options, NULL)) != -1) {
        switch (opt) {
            case 'l':
                list = true;
                execute = false;
                break;
            case 'p':
                poweroff = true;
                break;
            case 'h':
                help = true;
                break;
            default:
                help = true;
                return 1;
        }
    }
    if (help) {
        print_help(argv[0]);
        return 0;
    }
    pacman_t pacmans[MAX_PACMANS];
    size_t nb_pacmans = 0;
    char pacmans_path[MAX_PATH_LENGTH];
    if (get_path_from_config_dir(PACMANS_FILENAME, pacmans_path) != 0) {
        fprintf(stderr, "Error getting config directory path\n");
        return EXIT_FAILURE;
    }
    int res = read_pacmans_from_file(pacmans_path, pacmans, &nb_pacmans);
    if (res != 0) {
        fprintf(stderr, "Error reading pacmans from file: %s\n", pacmans_path);
        return EXIT_FAILURE;
    }
    
    if (list) {
        printf("Available package managers:\n");
        for (size_t i = 0; i < nb_pacmans; i++) {
            printf(" - %s\n", pacmans[i].name);
        }
    }

    if (execute) {
        pacmans_execute(pacmans, nb_pacmans, &feedback);
    }

    if (poweroff && execute) {
        printf(GREEN BOLD "[✓] Shutting down the system..." RESET "\n");
        #ifdef DEBUG
        system("echo 'shutdown now'");
        #else
        system("sleep 5 && shutdown now");
        #endif
    }
    return 0;
}
