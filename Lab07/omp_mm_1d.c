#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define TAM_COLUNA 500
#define TAM_LINHA 500
#define NUM_THREADS 8

/*
Como não quero gerar duas matrizes grandes para retornar em uma teceira, 
portanto, vou criar apenas uma matriz e multiplicar por ela mesma para inserir em uma segunda matriz
*/

int main() {
    int **matriz = (int **)calloc(TAM_LINHA, sizeof(int *));
    int **matriz_c = (int **)calloc(TAM_LINHA, sizeof(int *));
    
    for (int i = 0; i < TAM_LINHA; i++) {
        matriz[i] = (int *)calloc(TAM_COLUNA, sizeof(int));
        matriz_c[i] = (int *)calloc(TAM_COLUNA, sizeof(int));
    }

    // Inserindo dados na matriz para realizar a multiplicação:
    for (int i = 0; i < TAM_LINHA; i++) {
        for (int j = 0; j < TAM_COLUNA; j++) {
            matriz[i][j] = i + j;      // valor baseado na posição
        }
    }

    
    double inicio_seq = omp_get_wtime();
    // Aplicação de mapeamento 1D por linhas
    for (int i = 0; i < TAM_LINHA; i++) {
        for (int j = 0; j < TAM_COLUNA; j++) {
            for (int k = 0; k < TAM_LINHA; k++) {
                matriz_c[i][j] += matriz[i][k] * matriz[k][j];
            }
        }
    }

    double fim_seq = omp_get_wtime();
    double tempo_seq = fim_seq - inicio_seq;
    printf("Tempo seq: %.2f segundos\n", tempo_seq);

    int threads_usadas;
    double inicio_par = omp_get_wtime();
    // Aplicação de mapeamento 1D por linhas, paralelizando
    #pragma omp parallel for num_threads(NUM_THREADS)
    for (int i = 0; i < TAM_LINHA; i++) {
        threads_usadas = omp_get_num_threads();
        for (int j = 0; j < TAM_COLUNA; j++) {
            for (int k = 0; k < TAM_LINHA; k++) {
                matriz_c[i][j] += matriz[i][k] * matriz[k][j];
            }
        }
    }
    double fim_par = omp_get_wtime();
    double tempo_par = fim_par - inicio_par;
    printf("Tempo par: %.2f segundos para %d threads\n", tempo_par, threads_usadas);

    printf("Speedup: %.2fx\n", tempo_seq / tempo_par);

    // Liberando memória da matriz, primeiramente colunas e depois linhas
    for (int i = 0; i < TAM_LINHA; i++) {
        free(matriz[i]);
        free(matriz_c[i]);
    }

    free(matriz);
    free(matriz_c);

    return 0;
}