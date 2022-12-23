
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "libpmc.h"


void test1() {
    // test a triangle
    int ei[] = {0, 0, 1};
    int ej[] = {1, 2, 2}; 
    int output[3] = {0, 0, 0};
    
    int C = max_clique(3, ej, ei, 0, 3, output);
    if (C != 3) {
        fprintf(stderr, "Test failed");
        exit(-1);
    }
}      

int main(int argc, char **argv) {
    test1();
};
