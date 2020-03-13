/*
** EPITECH PROJECT, 2020
** PSU_malloc_2019
** File description:
** calloc
*/

#include "../include/malloc.h"
#include <string.h>

extern chunk_t *heap;

#ifdef DEBUG
void *my_calloc(size_t nmembr, size_t size)
#else
void *calloc(size_t nmembr, size_t size)
#endif
{
    #ifndef DEBUG
        void *ptr = malloc(size * nmembr);
    #else
        void *ptr = my_malloc(size * nmembr);
    #endif
    if (ptr != NULL)
        ptr = memset(ptr, 0, nmembr * size);
    return ptr;
}