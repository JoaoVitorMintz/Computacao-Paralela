#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define TAM_VETOR 100000000  // 100 milhões para notar diferença de tempo

int main() {
    int *A = (int *)calloc(TAM_VETOR, sizeof(int));
    int *B = (int *)calloc(TAM_VETOR, sizeof(int));
    int *C = (int *)calloc(TAM_VETOR, sizeof(int));

    if (!A || !B || !C) {
        printf("Erro: Memória insuficiente\n");
        return 1;
    }


    // Inserindo valores nos vetores de mesmo tamanho
    for (int i = 0; i < TAM_VETOR; i++) {
        A[i] = i;
        B[i] = i * 2;
    }

    // --- VERSÃO SEQUENCIAL ---
    clock_t inicio_seq = clock();
    for (int i = 0; i < TAM_VETOR; i++) {
        C[i] = A[i] + B[i];
    }
    clock_t fim_seq = clock();

    double tempo_seq = (double)(fim_seq - inicio_seq) / CLOCKS_PER_SEC;
    printf("Tempo sequencial: %.2f segundos\n", tempo_seq);

    // -- VERSÁO PARALELA ---
    double inicio_par = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < TAM_VETOR; i++) {
        C[i] = A[i] + B[i];
    }

    double fim_par = omp_get_wtime();
    double tempo_par = fim_par - inicio_par;
    printf("Tempo paralelo: %.2f segundos\n", tempo_par);
    printf("Speedup: %.2fx\n", tempo_seq / tempo_par);


    free(A);
    free(B);
    free(C);
    return 0;
}