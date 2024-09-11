#include "lib.h"

char* itoa(int value) {
    if (value == 0) {
        char* str = (char*)malloc(2 * sizeof(char)); 
        if (str == NULL) {
            return NULL;
        }
        str[0] = '0';
        str[1] = '\0';
        return str;
    }
    int temp = value;
    int length = 0;
    int is_negative = 0;
    
    if (value < 0) {
        is_negative = 1;
        temp = -temp;
    }

    do {
        length++;
        temp /= 10;
    } while (temp != 0);

    if (is_negative) {
        length++;
    }

    char* str = (char*)malloc((length + 1) * sizeof(char));
    if (str == NULL) {
        return NULL;
    }

    str[length] = '\0';

    temp = value;
    if (value < 0) {
        temp = -temp;
    }

    for (int i = length - 1; i >= 0; i--) {
        if (temp > 0) {
            str[i] = (temp % 10) + '0';
            temp /= 10;
        } else {
            if (is_negative) {
                str[i] = '-';
                is_negative = 0; 
            }
        }
    }
    return str;
}

void print_history(char * history_buffer) {
    while (*history_buffer) {
        printf("%c", *history_buffer);
        ++history_buffer;
    }
}