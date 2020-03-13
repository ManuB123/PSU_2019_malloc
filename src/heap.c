/*
** EPITECH PROJECT, 2020
** PSU_malloc_2019
** File description:
** heap
*/

#include "../include/malloc.h"

#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>

long int get_sbrk_size(long int size)
{
    long int res = (size - 1) / (2 * getpagesize()) * (2 * getpagesize()) 
            + (2 * getpagesize());
    return res;
}

bool init_heap(size_t size)
{
    heap = sbrk(0);
    heap = sbrk(get_sbrk_size(BLOCK_SIZE + size));
    if (heap == (void*)-1)
        return false;
    heap->chunk_size = get_sbrk_size(BLOCK_SIZE + size) - BLOCK_SIZE;
    heap->addr = (void*)heap + BLOCK_SIZE;
    heap->is_free = true;
    heap->next = NULL;
    heap->prev = NULL;
    return true;
}

static chunk_t *allocate_new_chunk(chunk_t *current, size_t size)
{
    chunk_t *new = sbrk(0);

    new = sbrk(get_sbrk_size(BLOCK_SIZE + size));
    if (new == (void*)-1)
        return (NULL);
    new->chunk_size = get_sbrk_size(BLOCK_SIZE + size) - BLOCK_SIZE;
    new->addr = (void*)new + BLOCK_SIZE;
    new->is_free = true;
    new->next = NULL;
    new->prev = current;
    return new;
}

void extend_heap(size_t size)
{
    chunk_t *current = heap;

    while (current != NULL && current->next != NULL)
        current = current->next;
    current->next = allocate_new_chunk(current, size);
}