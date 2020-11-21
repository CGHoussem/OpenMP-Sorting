#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "omp.h"
#include "string.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define DEBUG   0


typedef struct performance_measures {
    float generating_span;
    float sorting_span;
    float total_span;
} performance_measures;


performance_measures get_performance_measures(int n, int k, int nb_threads);

void create_tests_file(char* filename, int nk[][2], int nk_size, int nb_threads[]);


void d_dump_db(float** db, int n, int k);

/**
 * This function swaps two float pointers.
 * 
 * @param xp: the first float pointer
 * @param yp: the second float pointer
 ****/ 
void swap(float* xp, float* yp) {
    float temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selection_sort(float* bloc, int k) {
    for (int i = 0; i < k; i++) {
        int min_idx = i;
        for (int j = i + 1; j < k; j++) {
            if (*(bloc+j) < *(bloc+min_idx))
                min_idx = j;
        }
        swap(bloc+min_idx, bloc+i);
    }
}

void quick_sort(float* bloc, int l, int r) {
    if (l >= r) 
        return;

    float pivot = *(bloc + r);
    int cnt = 1;

    for (int i = 1; i <= r; i++) {
        if (*(bloc+i) <= pivot) {
            swap(bloc+cnt, bloc+i);
            cnt++;
        }
    }

    quick_sort(bloc, 1, cnt-2);
    quick_sort(bloc, cnt, r);
}

/**
 * This function sorts a bloc of floats.
 * 
 * @param bloc: The input to be sorted bloc
 * @param k: the size of the bloc
 *****/
void tri(float* bloc, int k){
    selection_sort(bloc, k);
    // quick_sort(bloc, 0, k-1);
}

/**
 * This function sorts two blocs in a way that the elements of 
 * the first bloc will be inferior the those in the second bloc.
 * 
 * @param bloc1: First bloc
 * @param bloc2: Second bloc
 * @param k: the size of the blocs
 *****/ 
void tri_merge(float* bloc1, float* bloc2, int k) {
    float* new_bloc = (float*) malloc(sizeof(float) * k*2);

    for (int i = 0; i < k*2; i++) {
        if (i < k)
            *(new_bloc+i) = *(bloc1+i);
        else
            *(new_bloc+i) = *(bloc2+i-k);
    }

    tri(new_bloc, k*2);
    for (int i = 0; i < k; i++){
        *(bloc1+i) = *(new_bloc+i);
        *(bloc2+i) = *(new_bloc+i+k);
    }

    free(new_bloc);
}

/**
 * This function generates and returns a table of K floats randomly.
 * 
 * @param k: the count of the generated numbers
 **/
float* generator(int k) {
    float* bloc = malloc(sizeof(float) * k);

    for (int i = 0; i < k; i++){
        *(bloc+i) = (float)rand()/RAND_MAX;
    }

    return bloc;
}

/**
 * This function frees the database out of the memory.
 * 
 * @param db: The database t be freed
 * @param n: The number of rows of the database
 **/
void free_db(float** db, int n) {
    for (int i = 0; i < n; i++) {
        free(*(db+i));
    }
    free(db);
}


/**
 * This functions sorts a database in a parallel way.
 * 
 * @param db: The database to be sorted
 * @param n: The number of rows of the database
 * @param k: the size of each row of the database
 ***/ 
float** parallel_sort(float** db, int n, int k) {
    int k_copie = k;
    #pragma omp parallel for
    for (int i = 0; i < n; i++) tri(*(db+i), k);

    for (int j = 0; j < n; j++) {
        int k = 1 + (j % 2);
        #pragma omp parallel for
        for (int i = 0; i < n/2; i++) {
            int b1 = (k + 2 * i) % n;
            int b2 = (k + 2 * i+1) % n;
            int min = MIN(b1, b2);
            int max = MAX(b1, b2);
            #if DEBUG==1
            printf("merge db[%d] et db[%d]\n", min, max);
            #endif
            tri_merge(*(db+min), *(db+max), k_copie);
        }
    }
}


int main(int argc, char** argv) {
    int nk[4][2] = 
    {
        {10, 10}, {100, 100}, {250, 250}, {500, 500},
        // {1000, 1000}, {10000, 10000},
        // {500, 500}, {500, 750}, {750, 500}, {750, 750},
        // {1000, 1000}, {1000, 2500}, {2500, 1000}, {2500, 2500},
        // {5000, 5000}, {5000, 7500}, {7500, 5000}, {7500, 7500},
        // {10000, 10000}, {10000, 15000}, {15000, 10000}
    };
    int nb_threads[6] = {1, 2, 4, 6, 8, 16};
    char name[100];
    strcpy(name, argv[1]);

    create_tests_file(name, nk, 4, nb_threads);

    return EXIT_SUCCESS;
}


void create_tests_file(char* filename, int nk[][2], int nk_size, int nb_threads[]) {
    printf("Creating %s.csv file...\n", filename);
    FILE* fp = NULL;
    filename = strcat(filename, ".csv");
    fp = fopen(filename, "w");
    // fprintf(fp, "TestID,\tN,\tK,\tNxK,\t#Threads,\tGenerating,\tSorting\tTotal\n");
    int test_id = 1;
    for (int i = 0; i < nk_size; i++) {
        int n = nk[i][0];
        int k = nk[i][1];
        for (int j = 0; j < 6; j++) {
            int nb_th = nb_threads[j];
            printf("Executing N:%d, K:%d, TH:%d...\n", n, k, nb_th);
            performance_measures pm = get_performance_measures(n, k, nb_th);
            fprintf(fp, "%d,\t%d,\t%d,\t%d,\t%d,\t%f,\t%f,\t%f\n", test_id++, n, k, n*k, nb_th, pm.generating_span, pm.sorting_span, pm.total_span);
        }
    }
    fclose(fp);
    printf("%s file created!\n", filename);
}

performance_measures get_performance_measures(int n, int k, int nb_threads) {
    performance_measures pm;
    srand((unsigned) time(NULL));
    
    omp_set_num_threads(nb_threads);
    
    double t1 = omp_get_wtime();
    float** db = (float**) malloc(sizeof(float*) * n);
    for (int i = 0; i < n; i++) {
        *(db+i) = NULL;
        *(db+i) = generator(k);        
    }
    double t2 = omp_get_wtime();
    pm.generating_span = t2 - t1;

    t1 = omp_get_wtime();
    parallel_sort(db, n, k);
    t2 = omp_get_wtime();

    pm.sorting_span = t2 - t1;

    pm.total_span = pm.generating_span + pm.sorting_span;

    free_db(db, n);
    return pm;
}



void d_dump_db(float** db, int n, int k) {
    for (int i = 0; i < n; i++) {
        printf("db[%d]\t", i);
        for (int j = 0; j < k; j++) {
            printf("%f\t", *(*(db+i)+j));
        }
        printf("\n");
    }
    printf("\n\n");
}

