/*
** EPITECH PROJECT, 2020
** PSU_2019_malloc
** File description:
** utilities
*/

#include "../include/malloc.h"
#include <stdio.h>

#ifdef DEBUG
void dump_heap(void)
{
    chunk_t *current = heap;
    int count = 0;

    while (current != NULL) {
        printf("chunk size:%i\n", current->chunk_size);
        current = current->next;
        count = -(~count);
    }
    while (current != NULL)
    {
        printf("chunk size:%i\n", current->chunk_size);
        current = current->prev;
    }
    
    printf("count : %i\n\n", count);
}
#endif