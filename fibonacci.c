#include "fibonacci.h"

unsigned long long recursiveFibonacci(unsigned long long *cache, int n){

    if (cache[n] == -1){
        cache[n] = recursiveFibonacci(cache, n-1) + recursiveFibonacci (cache, n-2);
    }
    return cache[n];
}

