#include "cipher.h"
#include <string.h>
#include <stdbool.h>

#define MIN_ASCII_VAL_UPPER  65
#define MAX_ASCII_VAL_UPPER  90
#define MIN_ASCII_VAL_LOWER  97
#define MAX_ASCII_VAL_LOWER 122
#define ALPHABET 26

/**
 * checks if the given num ascii value is upper case
 * @param num
 * @return 1 if upper case, 0 if not
 */
bool is_upper(int num) {
    if (num >= MIN_ASCII_VAL_UPPER && num <= MAX_ASCII_VAL_UPPER)
    { return 1;}
    else { return 0; }
}
/**
 * checks if the given num ascii value is lower case
 * @param num
 * @return 1 if lower case, 0 if not
 */
bool is_lower(int num) {
    if (num >= MIN_ASCII_VAL_LOWER && num <= MAX_ASCII_VAL_LOWER)
    {   return 1;}
    else { return 0; }
}


// See full documentation in header file
void encode(char s[], int k) {
    int len_s = strlen(s);
    int i;
k = k%ALPHABET;
    for (i = 0; i < len_s; i++) {
        if (is_upper(s[i])) {
            s[i] = (int) s[i] + k;
            if (!is_upper(s[i]) && s[i] > MAX_ASCII_VAL_UPPER) {
                s[i] = (char) s[i] - ALPHABET;
            }
            if (!is_upper(s[i]) && s[i] < MIN_ASCII_VAL_UPPER)
            {s[i] = (char) s[i] + ALPHABET;}
            else { s[i] = (char) s[i]; }
        }

        if (is_lower(s[i])) {
            s[i] = (int) s[i] + k;
            if (!is_lower(s[i]) && s[i] > MAX_ASCII_VAL_LOWER) {
                s[i] = (char) s[i] - ALPHABET;
            }
            if (!is_lower(s[i]) && s[i] < MAX_ASCII_VAL_LOWER)
            { s[i] = (char) s[i] + ALPHABET;}
            else { s[i] = (char) s[i]; }
        }
    }
}


// See full documentation in header file
void decode(char s[], int k) {
    int len_s = strlen(s);
    int i;
    k = k%ALPHABET;
    for (i = 0; i < len_s; i++) {
        if (is_upper(s[i])) {
            s[i] = (int) s[i] - k;
            if (!is_upper(s[i]) && (s[i] > MAX_ASCII_VAL_UPPER)) {
                s[i] = (char) s[i] - ALPHABET;
            }
            if (!is_upper(s[i]) && s[i] < MIN_ASCII_VAL_UPPER)
            {s[i] = (char) s[i] + ALPHABET;}
            else { s[i] = (char) s[i]; }
        }

        if (is_lower(s[i])) {
            s[i] = (int) s[i] - k;
            if (!is_lower(s[i]) && (s[i] > MAX_ASCII_VAL_LOWER)) {
                s[i] = (char) s[i] - ALPHABET;
            }
            if (!is_lower(s[i]) && s[i] < MAX_ASCII_VAL_LOWER)
            {  s[i] = (char) s[i] + ALPHABET;}
            else { s[i] = (char) s[i]; }
        }
    }
}


