/*
** EPITECH PROJECT, 2020
** PSU_malloc_2019
** File description:
** malloc
*/


#include "../include/malloc.h"

#include <unistd.h>
#include <string.h>
#include <stdio.h>

chunk_t *heap;
pthread_mutex_t malloc_thread_mutex = PTHREAD_MUTEX_INITIALIZER;

static void *malloc_extend(size_t size)
{
    void *ptr;

    extend_heap(size);
    if (heap == (void*)-1) {
        pthread_mutex_unlock(&malloc_thread_mutex);
        return (NULL);
    }
    ptr = find_block(size);
    return ptr;
}

#ifdef DEBUG
void *my_malloc(size_t size)
#else
void *malloc(size_t size)
#endif
{
    void *ptr = NULL;

    size = align2(size);
    if (size <= 0)
        return NULL;
    pthread_mutex_lock(&malloc_thread_mutex);
    if (heap == NULL)
        if (init_heap(size) == false) {
            pthread_mutex_unlock(&malloc_thread_mutex);
            return NULL;
        }
    if (heap == (void*) -1) {
        pthread_mutex_unlock(&malloc_thread_mutex);
        return (NULL);
    }
    ptr = find_block(size);
    if (ptr == NULL)
        ptr = malloc_extend(size);
    pthread_mutex_unlock(&malloc_thread_mutex);
    return ptr;
}
