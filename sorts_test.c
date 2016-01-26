#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "sorts.h"
	
/*void (*sort_ptr)(void *array, size_t length, Sort sort_func);*/

typedef void(*sort_func)(void *base, size_t num_of_elements, size_t element_size, cmp fp);

int IsBefore(const void *data1, const void *data2);
void CheckSorts(void *array, size_t length, sort_func SortFunc, FILE *fp);
void RandomArr(size_t arr[], size_t length);


int main(int argc, char* argv[], char** envp)
{
	FILE *fp1 = fopen("unsorted.txt", "w");
	FILE *fp2 = fopen("sorted.txt", "w");
	
	size_t random[100];
/*	size_t arr1[6] = {5, 2, 4, 6, 1, 3};*/
/*	size_t arr2[6] = {5, 2, 4, 6, 1, 3};*/
	
/*	size_t arr3[5] = {64, 25, 12, 22, 11};*/
/*	size_t arr4[5] = {64, 25, 12, 22, 11};*/
	
/*	size_t length1 = sizeof(arr1) / sizeof(size_t);*/
	
/*	size_t length2 = sizeof(arr3) / sizeof(size_t);*/
	size_t i = 0;
	
	RandomArr(random, 100);
	
	for( ; i < 100; ++i)
	{
		fprintf(fp1, "%lu\n", random[i]);
	}
	
	printf("\n________________InsertionSort________________\n");
	CheckSorts(random, 100, SortInsertion, fp2);
	
	printf("\n________________SelctionSort________________\n");
	RandomArr(random, 100);
	for(i = 0 ; i < 100; ++i)
	{
		fprintf(fp1, "%lu\n", random[i]);
	}
	CheckSorts(random, 100, SortSelction, fp2);
	
/*	puts("\n~~~~~~~~~with new array~~~~~~~\n");*/
/*	CheckSorts(arr3, length2, SortSelction);*/
	
/*	printf("\n________________BubbleSort________________\n");*/
/*	CheckSorts(arr4, length2, SortBubble, fp2);*/
	
/*	puts("\n~~~~~~~~~with new array~~~~~~~\n");*/
/*	CheckSorts(random, 100, SortBubble, fp2);*/
/*	puts("\n~~~~~~~~~with new array~~~~~~~\n");*/
/*	CheckSorts(arr1, length1, SortBubble);*/
	
	fclose(fp1);
	fclose(fp2);
	
	return(0);
}

int IsBefore(const void *data1, const void *data2)
{
	return(*(size_t*)data1 < *(size_t*)data2);
}

void CheckSorts(void *array, size_t length, sort_func SortFunc, FILE *fp)
{
	int i = 0;
	clock_t begin = 0, end = 0;
	double time_diff = 0;
	
	printf("array length:%lu\n", length);
	
/*	printf("\narray before:\n");*/
/*	for( ; i < length; ++i)*/
/*	{*/
/*		printf("arr[%d]:%lu\n", i, ((size_t*)array)[i]);*/
/*	}*/
	
	begin = clock();
	SortFunc(array, length, sizeof(size_t), &IsBefore);
	end = clock();
	
	time_diff = ((double)end - (double)begin) / CLOCKS_PER_SEC;
	printf("\ntime_diff InsertionSort:%f\n",time_diff);
	
	printf("\narray after:\n");
	for(i = 0; i < length; ++i)
	{
		fprintf(fp, "%lu\n", ((size_t*)array)[i]);
	}
}

void RandomArr(size_t arr[], size_t length)
{
	size_t i = 0;
	
	srand((unsigned)time(NULL));
	
	for( ; i < length; ++i)
	{
		arr[i] = rand();
	}
}
