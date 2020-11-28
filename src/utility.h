#ifndef UTILITY_H
#define UTILITY_H

#include "types.h"

// #define DEBUG   0
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

performance_measures get_performance_measures(int n, int k, int nb_threads);
void generate_performances(char* filename, int nk[][2], int nk_size, int nb_threads[], int nb_threads_size);

void swap(float* xp, float* yp);
void selection_sort(float* bloc, int k);
void quick_sort(float* bloc, int l, int r);

void tri(float* bloc, int k);
void tri_merge(float* bloc1, float* bloc2, int k);
float* generator(int k);
float** parallel_sort(float** db, int n, int k);

void free_db(float** db, int n);

void d_dump_db(float** db, int n, int k);

#endif