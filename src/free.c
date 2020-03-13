/*
** EPITECH PROJECT, 2020
** PSU_malloc_2019
** File description:
** free
*/

#include "../include/malloc.h"

extern chunk_t *heap;

#ifdef DEBUG
void my_free(void *ptr)
#else
void free(void *ptr)
#endif
{
    chunk_t *current = heap;

    while (current != NULL) {
        if (current->addr == ptr) {
            current->is_free = true;
            return;
        }
        current = current->next;
    }
}