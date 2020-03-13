/*
** EPITECH PROJECT, 2020
** PSU_2019_malloc
** File description:
** realloc
*/

#include "../include/malloc.h"

#include <string.h>

static void *realloc_extend(void *ptr, size_t size, chunk_t *current_chunk)
{
    void *res = NULL;

    #ifndef DEBUG
    res = (calloc(size + 1, 1));
    #else
    res = (my_calloc(size + 1, 1));
    #endif
    if (size < current_chunk->chunk_size)
        res = memcpy(res, ptr, size);
    else
        res = memcpy(res, ptr, current_chunk->chunk_size);
    #ifndef DEBUG
    free(ptr);
    #else
    my_free(ptr);
    #endif
    return res;
}

#ifdef DEBUG
void *my_realloc(void *ptr, size_t size)
#else
void *realloc(void *ptr, size_t size)
#endif
{
    chunk_t *current_chunk = NULL;
    void *res = NULL;
    
    if (heap == NULL || ptr == NULL)
    #ifndef DEBUG
        return (malloc(size));
    #else
        return (my_malloc(size));
    #endif
    else {
        current_chunk = find_chunk(ptr);
        if (current_chunk != NULL)
            res = realloc_extend(ptr, size, current_chunk);
        else
    #ifndef DEBUG
        return (malloc(size));
    #else
        return (my_malloc(size));
    #endif
    }
    return res;
}
#ifdef DEBUG
void *my_reallocarray(void *ptr, size_t nmemb, size_t size)
#else
void *reallocarray(void *ptr, size_t nmemb, size_t size)
#endif
{
    size_t new_size = 0;

    if (__builtin_umull_overflow(nmemb, size, &new_size))
        return (NULL);
    #ifndef DEBUG
    return realloc(ptr, nmemb * size);
    #else
    return my_realloc(ptr, nmemb * size);
    #endif
}