/*
	sorts
*/
	
#ifndef __SORTS_H__
#define __SORTS_H__

#include <stdio.h>

typedef int (*cmp)(const void *data1, const void *data2);

void SortInsertion(void *base, size_t num_of_elements, size_t element_size, cmp fp);

void SortSelction(void *base, size_t num_of_elements, size_t element_size, cmp fp);

void SortBubble(void *base, size_t num_of_elements, size_t element_size, cmp fp);

void CountingSort(void *base, 
				  size_t num_of_elements, 
				  size_t element_size, 
				  size_t(*produce_key)(const void *element, void *arg), 
				  void *arg,
				  size_t range);
	
#endif /* ifndef __SORTS_H__*/
