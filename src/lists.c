/*
** EPITECH PROJECT, 2020
** PSU_malloc_2019
** File description:
** lists
*/

#include <stddef.h>
#include <limits.h>
#include <unistd.h>

#include "../include/malloc.h"

void *split_chunk(chunk_t *block, size_t size)
{
    chunk_t *new;

    new = (void *)block->addr + size;
    new->chunk_size = block->chunk_size - size - BLOCK_SIZE;
    new->next = block->next;
    new->addr = (void *)new + BLOCK_SIZE;
    new->is_free = true;
    block->is_free = false;
    block->chunk_size = size;
    block->next = new;
    return (block);
}

void *find_block(size_t size)
{
    chunk_t *current = heap;
    chunk_t *best_result = NULL;
    chunk_t *tmp;

    while (current != NULL) {
        if (current->is_free == true &&
        (size_t)current->chunk_size > (size + BLOCK_SIZE)
        && (best_result == NULL 
        || (best_result != NULL &&
        best_result->chunk_size > current->chunk_size))) {
            best_result = current;
        }
        current = current->next;
    }
    if (best_result != NULL) {
        if ((size_t)best_result->chunk_size > (size + BLOCK_SIZE)) {
            tmp = split_chunk(best_result, size);
            return tmp->addr;
        }
    }
    return NULL;
}

chunk_t *find_chunk(void *ptr)
{
    chunk_t *current = heap;

    while (current != NULL) {
        if (current->addr == ptr)
            return current;
        current = current->next;
    }
    return NULL;
}