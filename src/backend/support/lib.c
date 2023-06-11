
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "garbage-collector.h"

char* strcatint_(const char* str, int num) {
    int str_len = strlen(str);
    int num_len = snprintf(NULL, 0, "%d", num);

    // allocate memory for the new string
    char* result = calloc_(str_len + num_len + 1, sizeof(char)); 

    // copy str into result
    strcpy(result, str);

    // append num to result
    sprintf(result + str_len, "%d", num);

    return result;
}

char * strcat_(const char* str1, const char* str2) {
 // calculate lengths of both strings
    int str1_len = strlen(str1);
    int str2_len = strlen(str2);

    // allocate memory for the new string
    // +2 for the null-terminator and the period
    char* result = calloc(str1_len + str2_len + 2, sizeof(char)); 

    // copy str1 into result
    strcpy(result, str1);

    // add a period after str1
    result[str1_len] = '.';

    // append str2 to result
    strcpy(result + str1_len + 1, str2);
    return result;
}
