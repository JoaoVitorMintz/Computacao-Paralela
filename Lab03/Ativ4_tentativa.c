#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define VECTOR_SIZE 1000
#define NUM_PROCESSES 4

// Funcao que calcula a soma de uma fatia de um vetor
long long sum_chunk(int* vector, int start, int end) {
    long long sum = 0;
    for (int i = start; i < end; i++) {
        sum += vector[i];
    }
    return sum;
}

int main() {
    int vector[VECTOR_SIZE];
    int total_sum_expected = 0;

    // Inicializa o vetor e calcula a soma esperada para verificacao
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector[i] = i + 1;
        total_sum_expected += vector[i];
    }

    int pipes[NUM_PROCESSES][2];
    pid_t pid;
    int chunk_size = VECTOR_SIZE / NUM_PROCESSES; 

    for (int i = 0; i < NUM_PROCESSES-1; i++) {
        if (pipe(pipes[i] == -1)) {
            perror("Pipe falhou ao ser gerado...");
            exit(EXIT_FAILURE);
        }

        pid = fork();

        if (pid == 0) { // Processo do filho
            close(pipes[i][0]); // Fecha o pipe para leitura apenas

            // Fechando as pontas dos outros pipes
            for (int j = 0; j < NUM_PROCESSES; j++) {
                if (i != j) {
                    close(pipes[j][0]);
                    close(pipes[j][1]);
                }
            }

            int inicio = i * chunk_size;
            int fim;

            if (i == NUM_PROCESSES -1) {
                fim = VECTOR_SIZE;
            } else {
                fim = (i + 1) * chunk_size;
            }

            sum_chunk(vector, inicio, fim);
            exit(0);

        } else if (pid > 0) { // Processo do pai

        } else {
            perror("Fork falhou...");
            exit(EXIT_FAILURE);
        }
    }
    
}