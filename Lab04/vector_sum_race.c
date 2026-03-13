// Soma de vetor com condição de corrida

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define TAM_VETOR 100000000
#define N 4

int* vet;
long long global_sum = 0;

typedef struct {
    int thread_id;
    int start;
    int end;
} ThreadArgs;


void* soma(void* args) {
    ThreadArgs* my_args = (ThreadArgs*)args;
    //long long local_sum = 0;

    for (int i = my_args->start; i < my_args->end; i++) {
        global_sum += vet[i];
    }

    //global_sum += local_sum;

    free(my_args);
    return NULL;
}



int main() {
    vet = (int*)malloc(TAM_VETOR * sizeof(int));
    long long expected_sum = 0;
    pthread_t threads[N];

    for (int i = 0; i < TAM_VETOR; i++) {
        vet[i] = 1;
        expected_sum += 1;
    }

    // Dividindo o tamanho do vetor para cada thread
    int divisao = TAM_VETOR / N;


    for (int i = 0; i < N; ++i) {
        ThreadArgs* args = (ThreadArgs*)malloc(sizeof(ThreadArgs));
        args->thread_id = i;
        args->start = i * divisao;
        args->end = (i == N - 1) ? TAM_VETOR : (i + 1) * divisao;
        
        pthread_create(&threads[i], NULL, soma, args);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nValor esperado: %lld", expected_sum);
    printf("\nValor global calculado: %lld\n", global_sum);

    free(vet);
    return 0;
}