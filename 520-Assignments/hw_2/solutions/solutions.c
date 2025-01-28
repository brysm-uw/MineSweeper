#include "solutions.h"
#include <stdio.h>
#include <stdlib.h>

int running_total(int n) {
    static int total = 0;
    total += n;
    return total;
}
int* reverse(int* input, int len) {
    int* reversed = (int*)calloc(len, sizeof(int));
    if(!reversed) {
        return NULL;
    }
    for(int idx = 0; idx < len; idx++) {
        *(reversed + idx) = input[len - 1 - idx];
    }
    return reversed;
}
void reverse_in_place(int* x, int len) {
    for(int idx = 0; idx < len / 2; idx++) {
        *(x + idx) = *(x + idx) ^ *(x + len - 1 - idx);
        *(x + len - 1 - idx) = *(x + idx) ^ *(x + len - 1 - idx);
        *(x + idx) = *(x + idx) ^ *(x + len - 1 - idx);
    }
}
int num_occurences(int *x, int len, int val) {
    int ctr = 0;
    for(int idx = 0; idx < len; idx++) {
        if(*(x + idx) == val) {
            ctr++;
        }
    }
    return ctr;
}