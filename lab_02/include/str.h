#include <stdlib.h> // for size_t
#ifndef STR_H_
#define STR_H_

char* str_cpy(char* dest, char* src);

char* str_cat(char* dest, char* src);

int str_cmp(char* str1, char* str2);

size_t str_len(char* str);

#endif
