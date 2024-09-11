#include "lib.h"

int main() {
    char * history = (char *) mmap(NULL, sysconf(_SC_PAGE_SIZE), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    char shell_name[SHELL_NAME_SIZE];
    strcpy(shell_name, "myshell");
    int command_count = 1;
    char command[COMMAND_SIZE] = {0};
    char arguments[ARGUMENTS_SIZE] = {0};
    char current_working_directory[CWD_SIZE] = {0};
    getcwd(current_working_directory, CWD_SIZE);
    int flag = 1;
    while(1) {
        
        if (flag) {
            printf("\033[33m%s> \033[0m", shell_name);
            scanf("%s", command);
        }
        else printf("\033[35m%s\033[0m\n", command);
        if (!strcmp(command, "exit")) {
            printf("Exiting...\n");
            return 0;
        } else if (!strcmp(command, "clear")) {
            system("clear");
            flag = 1;
        } else if (!strcmp(command, "pwd")) {
            printf("%s\n", current_working_directory);
            flag = 1;
        } else if (!strcmp(command, "cd")) {
            if (flag) {
                getchar();
                fgets(arguments, ARGUMENTS_SIZE - 2, stdin);
                arguments[strlen(arguments) - 1] = '\0';
            }
            if (chdir(arguments)) {
                printf("myshell: cd: %s: No such file or directory\n", arguments);
            }
            getcwd(current_working_directory, CWD_SIZE);
            flag = 1;
        } else if (!strcmp(command, "help")) {
            printf("Available commands:\n");
            printf("cd /pathname       - change directory\n");
            printf("history            - get command history\n");
            printf("pwd                - print working directory\n");
            printf("echo \"Hello\"       - print Hello\n");
            printf("clear              - clear working space\n");
            printf("setenv VAR value   - set your environment\n");
            printf("unsetenv VAR       - unset your environment\n");
            printf("chprompt \"bash\"    - change prompt name\n");
            printf("printenv            - print environment variables\n");
            flag = 1;
        } else if (!strcmp(command, "history")) {
            print_history(history);
            flag = 1;
        } else if (!strcmp(command, "echo")) {
            if (flag) {
                getchar();
                fgets(arguments, ARGUMENTS_SIZE, stdin);
                arguments[strlen(arguments) - 1] = '\0';
            }
            if (arguments[0] == '$') {
                // Get environment variable and print
            } else {
                printf("%s\n", arguments);
            }
            flag = 1;
        } else if (command[0] == '!') {
            char * ind = (char *) malloc(sizeof(int) * IND_SIZE);
            assert(ind != NULL);
            strcpy(ind, &command[1]);
            char * ptr = strstr(history, ind);
            while (*ptr++ != ' ');
            ptr++;
            memset(command, 0, COMMAND_SIZE);
            int i;
            for (i = 0; ptr[i] != ' ' && ptr[i] != '\n'; ++i) {
                command[i] = ptr[i];
            }
            if (ptr[i] == ' ') {
                ++i;
                int j;
                for (j = 0; ptr[j + i] != '\n'; ++j) {
                    arguments[j] = ptr[j + i];
                }
            }
            flag = 0;
        } else if (!strcmp(command, "chprompt")) {
            if (flag) {
                scanf("%s", arguments);
            }
            strcpy(shell_name, arguments);
            flag = 1;
        } else if (!strcmp(command, "setenv")) {
            if (flag) {
                getchar();
                fgets(arguments, ARGUMENTS_SIZE - 2, stdin);
                arguments[strlen(arguments) - 1] = '\0';
            }
            char first_argument[ARGUMENTS_SIZE / 2] = {0};
            char second_argument[ARGUMENTS_SIZE / 2] = {0};
            int i;
            for (i = 0; arguments[i] != ' '; ++i) {
                first_argument[i] = arguments[i];
            }
            first_argument[i] = '\0';
            ++i;
            strcpy(second_argument, &arguments[i]);
            setenv(first_argument, second_argument, 0);
            flag = 1;
        } else if (!strcmp(command, "printenv")) {
            system("printenv");
            flag = 1;
        } else if (!strcmp(command, "unsetenv")) {
            if (flag) {
                scanf("%s", arguments);
            }
            unsetenv(arguments);
            flag = 1;
        }
        
        else {
            printf("No such command\n");
            flag = 1;
        }

        char * ind = itoa(command_count);
        strcat(history, ind);
        free(ind);
        strcat(history, "  ");
        strcat(history, command);
        strcat(history, " ");
        strcat(history, arguments);
        strcat(history, "\n");
        ++command_count;
        if (flag) {
            memset(command, 0, COMMAND_SIZE);
            memset(arguments, 0, ARGUMENTS_SIZE);
        }
    }
}