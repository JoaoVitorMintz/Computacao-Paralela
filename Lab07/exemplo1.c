#include <stdio.h>
#include <omp.h>

int main() {
    printf("--- Fora da região paralela ---");
    printf("Número de processadores disnoíveis: %d\n", omp_get_num_procs());
    printf("Número de threads (antes de definir): %d\n", omp_get_num_threads());

    // Define o número de threads para a próxima região paralela (caso queira definir):
    omp_set_num_threads(4);

    #pragma omp parallel
    {
        // Dentro desta diretiva, define que este bloco será executado por 4 threads
        // A diretiva 'master' a seguir garante que este trecho só seja executado pela thread 0
        #pragma omp master
        {
            printf("\n--- Dentro da região paralela ---\n");
            printf("Número de threads na equipe: %d\n", omp_get_num_threads());
        }

        // Esta diretiva garante que todas as threads esperem a master imprimir antes de continuar
        #pragma omp barrier
        
        // Cada thread imprime seu próprio ID
        // Utilizado 'critical' para evitar saídas se misturem no console
        #pragma omp critical
        {
            printf("Olá! Eu sou a thread %d de $d.\n", omp_get_thread_num(), omp_get_num_threads());
        }
    }

    printf("\n--- Fora da região paralela de novo ---\n");
    printf("Número de threads: %d\n", omp_get_num_threads());

    return 0;
}