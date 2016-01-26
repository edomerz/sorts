#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>


#include "sorts.h"

void swap(void *data1, void *data2, void *tmp, size_t element_size)
{
	memmove(tmp, data1, element_size);
	memmove(data1, data2, element_size);
	memmove(data2, tmp, element_size);
}

void(SortInsertion(void *base,
				   size_t num_of_elements, 
				   size_t element_size, 
				   cmp fp))
{
	void *tmp = malloc(element_size);
	char *iter = (char*)base;
	char *next = iter + element_size;
	char *prev = iter;
	
	while(num_of_elements - 1)
	{
		while((prev >= (char*)base) && (!fp(prev, next)))
		{
			swap(prev, next, tmp, element_size);
			next -= element_size;
			prev -= element_size;
		}
		iter += element_size;
		next = iter + element_size;
		prev = iter;
		--num_of_elements;
	}
	free(tmp);
}

void(SortSelction(void *base,
				   size_t num_of_elements,
				   size_t element_size,
				   cmp fp))
{
	void *tmp = malloc(element_size);

	char *new_start = (char*)base + element_size;
	char* iter 		= new_start;
	char *end = (char*)base + (num_of_elements * element_size);

	char *first = (char*)base;

	while(new_start != end)
	{
		for(iter = new_start; iter != end; iter += element_size)
		{
			if(!fp(first, iter))
			{
				first = iter;
			}
		}
		swap(first, new_start - element_size, tmp, element_size);

		first = new_start;
		new_start += element_size;
	}
	free(tmp);
}

void(SortBubble(void *base,
				   size_t num_of_elements,
				   size_t element_size,
				   cmp fp))
{
	void *tmp = malloc(element_size);
	char *start = (char*)base;
	char *end = start + num_of_elements * element_size;
	char *iter = start;
	char *next = iter + element_size;

	while((end - start) != (element_size))
	{
		for(iter = start, next = iter + element_size;
			next != end;
			iter += element_size, next += element_size)
		{
			if(!fp(iter, next))
			{
				swap(iter, next, tmp, element_size);
			}
		}
		end -= element_size;
	}
	free(tmp);
}

void CountingSort(void *base,
				  size_t num_of_elements,
				  size_t element_size,
				  size_t(*produce_key)(const void *element, void *arg),
				  void *arg,
				  size_t range)
{
	char *start = (char*)base;
	char *iter = start;
	char *end = start + (num_of_elements * element_size);
	size_t i = 1;
	size_t length = range * sizeof(size_t);

	size_t * count = (size_t*)malloc(length);
	char *sorted = (char*)malloc(num_of_elements * element_size);
	assert(count);
	assert(sorted);

	while(iter != end)
	{
		++(count[produce_key((void*)iter, arg)]);
		iter += element_size;
	}

	for( ; i < range; ++i)
	{
		count[i] +=  count[i - 1];
	}

	iter = end - element_size;
	while(iter >= start)
	{
		memove( (sorted + ((count[produce_key((void*)iter, arg)] - 1) * element_size)), 
			     iter, 
			     element_size)
		iter -= element_size;
	}

	memmove(base, (void*)sorted, num_of_elements * element_size);

	free(count);
	free(sorted);

	return;
}

