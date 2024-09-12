#ifndef LIB
#define LIB

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <string.h>
#include <sys/mman.h>

#define COMMAND_SIZE 128
#define CWD_SIZE 512
#define ARGUMENTS_SIZE 512
#define IND_SIZE 64
#define SHELL_NAME_SIZE 64

char * itoa(int value);
void print_history(char * history_buffer);

#endif