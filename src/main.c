#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "utility.h"

int main(int argc, char** argv) {

    int nb_threads[4] = {1, 2, 4, 8};
    int nk[21][2] = 
    {
        // 256
        {8, 32}, {16, 16}, {32, 8},
        // 1 024
        {16, 64}, {32, 32}, {64, 16},
        // 4 096
        {8, 512}, {64, 64}, {512, 8},
        // 16 384
        {32, 512}, {128, 128}, {512, 32},
        // 65 536
        {64, 1024}, {256, 256}, {1024, 64},
        // 262 144
        {16, 16384}, {512, 512}, {16384, 16},
        // 1 048 576
        {32, 32768}, {1024, 1024}, {32768, 32},
    };
    
    generate_performances("performances.csv", nk, 21, nb_threads, 4);

    return EXIT_SUCCESS;
}
