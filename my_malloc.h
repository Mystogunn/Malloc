/*
** EPITECH PROJECT, 2018
** my_malloc
** File description:
** my_malloc.h
*/

#ifndef _MY_MALLOC_H_
# define _MY_MALLOC_H_

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define MARGIN_SIZE 20

extern void *malloc(size_t size);
extern void free(void *ptr);
extern void *realloc(void *ptr, size_t size);
extern void *calloc(size_t num, size_t nsize);

typedef struct chunk chunk_t;
typedef struct chunk_handling chunk_handling_t;

chunk_t *check_free_block(size_t size);
chunk_t *create_new_block(size_t size);
chunk_t *split_block(chunk_t *chunk, size_t size);
void merge_block(void);

struct chunk {
	size_t size;
	unsigned is_free;
	chunk_t *prev;
	chunk_t *next;
};

#endif