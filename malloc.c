/*
** EPITECH PROJECT, 2018
** PSU_2021_malloc
** File description:
** malloc.c
*/

#include <pthread.h>
#include "my_malloc.h"

chunk_t *front;
chunk_t *back;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *malloc(size_t size)
{
	chunk_t *new_ptr = NULL;
	size_t tozz = size * sizeof(size_t);

	if (tozz <= 0)
		return (NULL);
	pthread_mutex_lock(&mutex);
	if ((new_ptr = check_free_block(tozz)) != NULL) {
		new_ptr->is_free = 0;
		pthread_mutex_unlock(&mutex);
		return ((void *)(new_ptr + 1));
	}
	else if ((new_ptr = create_new_block(tozz)) == NULL) {
		pthread_mutex_unlock(&mutex);
		return (NULL);
	}
	pthread_mutex_unlock(&mutex);
	return ((void*)(new_ptr + 1));
}

chunk_t *check_free_block(size_t size)
{
	chunk_t *current = front;
	chunk_t *tmp = NULL;
	size_t min = 0;

	while (current) {
		if (current->is_free == 1 && (current->size >= size &&
		current->size < (size + sizeof(chunk_t) + MARGIN_SIZE)))
			return (current);
		else if (current->is_free == 1 &&
		current->size >= (size + sizeof(chunk_t) + MARGIN_SIZE) &&
		(min == 0 || min < size)) {
			tmp = current;
			min = current->size;
		}
		current = current->next;
	}
	return (split_block(tmp, size));
}

chunk_t *split_block(chunk_t *chunk, size_t size)
{
	chunk_t *new_ptr = NULL;

	if (!chunk)
		return (NULL);
	chunk->size -= size;
	new_ptr = (chunk_t *)((char*) chunk + chunk->size);
	new_ptr->size = size;
	new_ptr->is_free = 0;
	new_ptr->prev = chunk;
	new_ptr->next = chunk->next;
	chunk->next = new_ptr;
	chunk->size -= sizeof(chunk_t);
	if (new_ptr->next)
		new_ptr->next->prev = new_ptr;
	return (new_ptr);
}

chunk_t *create_new_block(size_t size)
{
	chunk_t *new_ptr = NULL;

	new_ptr = sbrk(size + sizeof(chunk_t));
	if (new_ptr == (void*) -1) {
		return (NULL);
	}
	new_ptr->size = size;
	new_ptr->is_free = 0;
	new_ptr->prev = back;
	new_ptr->next = NULL;
	if (!front)
		front = new_ptr;
	if (back)
		back->next = new_ptr;
	back = new_ptr;
	return (new_ptr);
}