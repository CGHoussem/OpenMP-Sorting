#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "utility.h"

int main(int argc, char** argv) {

    if (argc < 2)
        return printf("SYNTAX: ./program [filename]\n"), 1;

    char* filename = (char*) malloc(sizeof(char) * 32);
    strcpy(filename, argv[1]);

    // concat .csv extension to the filename if it doesn't exist
    if (strpos(filename, ".csv") == -1)
        strcat(filename, ".csv");
    
    int nb_threads[4] = {1, 2, 4, 8};
    int nk[21][2] = 
    {
        // 1 024
        {16, 64}, {32, 32}, {64, 16},
        // 4 096
        {16, 512}, {64, 64}, {512, 16},
        // 16 384
        {32, 512}, {128, 128}, {512, 32},
        // 65 536
        {128, 512}, {256, 256}, {512, 128},
        // 262 144
        {256, 1024}, {512, 512}, {1024, 256},
        // 1 048 576
        {512, 2048}, {1024, 1024}, {2048, 512},
        // // 4 194 304
        {512, 8192}, {2048, 2048}, {8192, 512},
    };
    
    generate_performances(filename, nk, 21, nb_threads, 4);

    free(filename);
    return EXIT_SUCCESS;
}
