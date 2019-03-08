#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "mergesort.h"

void mergesort(void* base, size_t num, size_t size, int (*compar)(const void*,const void*)) {
    if(num > 1) {
        size_t s = (num + 1) / 2;
        mergesort(base, s, size, compar);
        mergesort(base + s * size, num - s, size, compar);
        merge(base, num, size, compar);
    }
}

void merge(void* base, size_t num, size_t size, int (*compar)(const void*,const void*)) {
    size_t s = (num + 1)/2;
    char* pre = malloc(s * size);
    char* p1 = memcpy(pre, base, size * s);
    char* buffer = base;
    char* p2 = buffer + size * s;
    size_t i = 0, j = s;
    while(i < s) {
        if(j == num || compar(p1, p2) <= 0) {
            for (size_t it = 0; it < size; it++)
                *buffer++ = *p1++;
            i++;
        } else {
            for (size_t it = 0; it < size; it++)
                *buffer++ = *p2++;
            j++;
        }
    }
    free(pre);
}