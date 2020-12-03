#ifndef UTILITY_H
#define UTILITY_H

#include "types.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

// Functional methods
float* generator(int k);
void selection_sort(float **bloc, int k);
void heapify(float **bloc, int bloc_size, int i);
void heap_sort(float** bloc, int bloc_size);

// Asked methods
void tri(float **bloc, int k);
void tri_merge(float **bloc1, float **bloc2, int k);
void parallel_sort(float ***db, int n, int k, performance_measures* pm);

// Important methods
performance_measures get_performance_measures(int n, int k, int nb_threads);
void generate_performances(char* filename, int nk[][2], int nk_size, int nb_threads[], int nb_threads_size);

// Utility methods
void swap(float* xp, float* yp);
void free_db(float** db, int n);
void d_dump_db(float** db, int n, int k);
int strpos(char *haystack, char *needle);

#endif