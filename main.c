#include <stdio.h>

#include "fibonacci.h"

int main(int argc, char *argv[]){
    
    int n;

    printf("Digite o termo de fibonacci desejado: ");
    scanf("%i", &n);

    unsigned long long  answer[n];
    answer[0] = 0;
    answer[1] = 1;

    for (int i = 2; i < n; i++){
        answer[i] = -1;
    }
    recursiveFibonacci(answer, n-1);

    for (int i = 0; i < n; i++) {
        printf("%i : %llu \n", i+1, answer[i]);
    }
    return 0;
}
