/*
** EPITECH PROJECT, 2021
** new_malloc
** File description:
** Created by Yoann Sarkissian,
*/

#include "my_malloc.h"

extern chunk_t *front;
extern chunk_t *back;
pthread_mutex_t mutex;

void more_chunk(void)
{
	chunk_t *tmp;

	tmp = front;
	while (tmp != NULL) {
		if (tmp->next == back) {
			tmp->next = NULL;
			back = tmp;
		}
		tmp = tmp->next;
	}
}

void free(void *block)
{
	chunk_t *chunk;
	void *brk_point = sbrk(0);

	if (block != NULL) {
		pthread_mutex_lock(&mutex);
		chunk = (chunk_t *)block - 1;
		if ((char *)block + chunk->size == brk_point) {
			(front == back) ? (front = back = NULL) : more_chunk();
			sbrk(0 - sizeof(chunk_t) - chunk->size);
			pthread_mutex_unlock(&mutex);
			return;
		}
		chunk->is_free = 1;
		pthread_mutex_unlock(&mutex);
	}
}

void *realloc(void *ptr, size_t size)
{
	chunk_t *chunk;
	size_t tozz = size * sizeof(size_t);
	void *ret = NULL;


	if (ptr == NULL || tozz == 0)
		ret = malloc(size);
	else {
		chunk = (chunk_t *)ptr - 1;
		(chunk->size >= tozz) ? ret = ptr : 0;
		(ret == NULL) ? ret = malloc(size) : 0;
		if (ret != NULL && ret != ptr) {
			memcpy(ret, ptr, chunk->size);
			free(ptr);
		}
	}
	return (ret);
}

void *calloc(size_t nmemb, size_t size)
{
	size_t s;
	void *ret = NULL;

	if (nmemb == 0 || size == 0 || (s = (nmemb * size)) == 0)
		return (ret);
	(size == s / nmemb) ? ret = malloc(s) : 0;
	(ret != NULL) ? memset(ret, 0, s) : 0;
	return (ret);
}