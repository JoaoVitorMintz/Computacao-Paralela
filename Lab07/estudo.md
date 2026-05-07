# Conteúdo estudado

## Relacionando a teoria à prática deste laboratório

### Resumo OpenMP:
OpenMP é uma API padrão da indústria para Multi-Processamento, muito comum para processadores
multicore e servidores multiprocessados (SMP). Diferente de bibliotecas como Pthreads onde o programador
gerencia manualmente as trheads, o OpenMP utiliza diretivas de compilador, isto é, o programador indica partes em que deseja paralelizar no código serial e o compilador executa esses trechos em paralelo. Portanto, o encarregado de gerar o código complexo de gerenciamento e criação de threads.

O OpenMP utiliza o modelo de execução Fork-Join, iniciando com uma única thread de execução (**thread mestre**). Ao encontrar uma diretiva OpenMP, athread mestre realiza o fork, criando uma equipe de **threads trabalhadoras**. A mestre e as trabalhadoras executam o código da região paralela. Ao final, as trabalhadoras realizam o join à thread mestre, que continua a execução sequencial sozinha.

Apesar de sua força na indústria, um grande problema do OpenMP é que não foi projetado para programação em clusters de memória distribuída, sendo este o domínio do MPI.

### Característica do OpenMP para manter dados:

No OpenMP, podemos definir variáveis como shared e private, declarando com a cláusula ou, na melhor prática, declarando dentro do laço para evitar condição de corrida.

### Resolvendo Condições de Corrida: Agregações

#### Problema: Soma de todos os elementos de um vetor:

```C
double soma = 0.0;
for (int i = 0; i < N; i++) {
    soma += vetor[i];
}
```

#### Solução 1: Força Bruta com critical

```C
double soma = 0.0;
#pragma omp parallel for
for (int i = 0; i < N; i++) {
    #pragma omp critical
    {
        soma += vetor[i];
    }
}
```
**Análise:** Esta abordagem funciona, entretanto, é muito ineficiente, já que as threads formarão uma "fila" de execução para somar uma de cada vez. Ganho de paralelismo será muito baixo.

#### Solução 2: Forma Elegante e Eficiente com reduction

```C
double soma 0.0;
#pragma omp parallel for reduction(+:soma)
for (int i = 0; i < N; i++) {
    soma += vetor[i];
}
```
**Análise:** Esta cláusura instrui o OpenMP à: Criar uma cópia **privada** da soma para cada thread, inicializando com 0, em seguida, cada thread acumula suas somas parciais, sem condição de corrida. Por fim, o OpenMP combina (reduz) os valores de todas as cópias privadas e armazena o resultado na variável soma original.

