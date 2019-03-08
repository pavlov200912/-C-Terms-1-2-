#include "mergesort.h"
#include <stdio.h>
#include <string.h>

typedef int(*binary)(int, int);

int cmpint(const void *a, const void* b) {
    const int *pi1 = a;
    const int *pi2 = b;
    return (*pi1 - *pi2);
}

int cmpstr(const void *a, const void *b) {
    return strcmp(*(char **) a, *(char **) b);
}

int cmpchar(const void *a, const void *b) {
    const char *p1 = a;
    const char *p2 = b;
    return (*p1 - *p2);
}

int main(int args, char *argv[]) {
    if(args == 1) {
        printf("Data type not found\n");
        return 0;
    }
    if(!strcmp(argv[1], "int")) {
        int* base = malloc(sizeof(int) * (args - 2));
        for(int i = 2; i < args; i++) {
            base[i - 2] = atoi(argv[i]);
        }
        mergesort(base, args - 2, sizeof(int), cmpint);
        for(int i = 0; i < args - 2; i ++) {
            printf("%d ", base[i]);
        }
        free(base);
    } else if(!strcmp(argv[1], "str")) {
        mergesort(argv + 2, args - 2, sizeof(char*), cmpstr);
        for(int i = 2; i < args; i ++) {
            printf("%s ", argv[i]);
        }

    } else if(!strcmp(argv[1], "char")) {
        char* base = malloc(sizeof(char) * (args - 2));
        for(int i = 2; i < args; i++) {
            base[i - 2] = argv[i][0];
        }
        mergesort(base, args - 2, sizeof(char), cmpchar);
        for(int i = 0; i < args - 2; i ++) {
            printf("%c ", base[i]);
        }
        free(base);
    }
}