// Valor máximo do vetor sem condição de corrida
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define TAM_VETOR 10000
#define N 4

int *vet;
int *respsGlobal;

typedef struct {
    int thread_id;
    int inicio;
    int fim;
} ThreadArgs;

int maxReal() {
    int maior = 0;

    for (int i = 0; i < N; i++) {
        if (respsGlobal[i] > maior) {
            maior = respsGlobal[i];
        }
    }

    return maior;
}

void* max(void* args) {
    ThreadArgs* my_args = (ThreadArgs*)args;
    int maior = 0;

    for (int i = my_args->inicio; i < my_args->fim; i++) {
        if (vet[i] > maior) {
            maior = vet[i];
        }
    }

    respsGlobal[my_args->thread_id] = maior;

    printf("Thread %d realizou o processo!\n", my_args->thread_id);
    free(my_args);
    return NULL;
}

int main() {
    vet = (int*)malloc(TAM_VETOR * sizeof(int));
    respsGlobal = (int*)malloc(N * sizeof(int));
    srand(time(NULL));
    pthread_t threads[N];


    for(int i = 0; i < TAM_VETOR; i++) {
        vet[i] = rand();
    }

    int divisao = TAM_VETOR / N;

    for (int i = 0; i < N; i++) {
        ThreadArgs* args = (ThreadArgs*)malloc(sizeof(ThreadArgs));
        args->thread_id = i;
        args->inicio = divisao * i;
        
        if (i == N - 1) {
            args->fim = TAM_VETOR;
        } else {
            args->fim = (i + 1) * divisao;
        }

        pthread_create(&threads[i], NULL, max, args);
    }

    for (int j = 0; j < N; j++) {
        pthread_join(threads[j], NULL);
    }

    int maiorReal = maxReal();

    printf("Maior valor: %d\n", maiorReal);

    free(vet);
    free(respsGlobal);
    return 0;
}