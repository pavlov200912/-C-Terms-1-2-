#include <stddef.h>
#include <stdlib.h>
#ifndef __MERGESORT_H__
#define __MERGESORT_H__
void merge(void* base, size_t num, size_t size, int (*compar)(const void*,const void*));
void mergesort(void* base, size_t num, size_t size, int (*compar)(const void*,const void*));
#endif