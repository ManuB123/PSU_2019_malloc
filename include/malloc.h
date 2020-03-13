/*
** EPITECH PROJECT, 2020
** PSU_malloc_2019
** File description:
** malloc
*/

#ifndef MALLOC_H_
#define MALLOC_H_

#include <stdbool.h>

#include <pthread.h>

#include <stddef.h>


typedef struct chunk_s {
    bool is_free;
    void *addr;
    int chunk_size;
    char issou[1];
    struct chunk_s *next;
    struct chunk_s *prev;
} chunk_t;

#define BLOCK_SIZE sizeof(chunk_t)

#define align2(x) (((((x)-1)>>2)<<2)+4)

// static chunk_t *heap = NULL;

extern chunk_t *heap;

void extend_heap(size_t size);
bool init_heap(size_t);
long int get_sbrk_size(long int size);
void *find_block(size_t size);
void dump_heap(void);

void free(void *ptr);
void *calloc(size_t nmembr, size_t size);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);
void my_free(void *ptr);
void *my_calloc(size_t nmembr, size_t size);
void *my_malloc(size_t size);
void *my_realloc(void *ptr, size_t size);
void *my_reallocarray(void *ptr, size_t nmemb, size_t size);
chunk_t *find_chunk(void *ptr);

#endif /* !MALLOC_H_ */
