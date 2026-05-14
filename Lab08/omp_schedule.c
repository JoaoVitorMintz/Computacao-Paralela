#include <stdio.h>
#include <omp.h>
#include <unistd.h>

#define N 16
#define CHUNK_SIZE 4

int main() {
    printf("--- Testando schedule(static, %d) ---\n", CHUNK_SIZE);
    #pragma omp parallel for schedule(static, CHUNK_SIZE)
    for (int i = 0; i < N; ++i) {
        usleep((i % 4) * 10000);
        printf("Thread %d processou a iteração %d\n", omp_get_thread_num(), i);
    }

    printf("\n--- Testando schedule(dynamic, %d) ---\n", CHUNK_SIZE);
    #pragma omp parallel for schedule(dynamic, CHUNK_SIZE)
    for (int i = 0; i < N; ++i) {
        usleep((i % 4) * 10000);
        printf("Thread %d processou a iteração %d\n", omp_get_thread_num(), i);
    }

    printf("\n--- Testando schedule(guided) ---\n");
    #pragma omp parallel for schedule(guided)
    for (int i = 0; i < N; ++i) {
        usleep((i % 4) * 10000);
        printf("Thread %d processou a iteração %d\n", omp_get_thread_num(), i);
    }

    printf("\n--- Testando schedule(auto) ---\n");
    #pragma omp parallel for schedule(auto)
    for (int i = 0; i < N; ++i) {
        usleep((i % 4) * 10000);
        printf("Thread %d processou a iteração %d\n", omp_get_thread_num(), i);
    }

    return 0;
}