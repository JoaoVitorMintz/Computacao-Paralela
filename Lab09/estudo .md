# Conteúdo estudado

## Relacionando a teoria à prática deste laboratório

O desempenho é limitado por duas paredes: A **"Parede da Memória"** (localidade de cache) e a **"Parede da Sincronização"** (overheads).

 - **Localidade de Cache**: Acessar dados na RAM é centenas de vezes mais lento que acessá-las no cache L1. Algoritmos que desrespeitem a localidade (ex: ijk) gastam 99% do tempo esperando a memória, não calculando.
 - **Overhead de Sincronização**: Algoritmos que exigem muitas barreiras (ex: Odd-Even Sort) forçam as threads a parar e esperar constantemente. O custo da sincronização pode ser maior que o ganho do paralelismo.

## Ferramentas de Análise de Cache:

Para provar a ocorrência de **Cache Misses**, precisamos de um profiler. Para isso, pode-se usar o **perf** ou o **cachegring** (conhecido também como valgrind).

Comando para rodar o valgrind:

```terminal
valgrind --tool=cachegrind ./meu_programa
```

O **cachegrind** gera um resumo da seguinte forma:

```terminal
==12345== D refs: 89,539,191 (60,123,456 rd + 29,415,735 wr)
==12345== D1 misses: 40,730,582 (20,123,456 rd + 20,607,126 wr)
==12345== LLd misses: 10,123,456 ( 5,123,456 rd + 5,000,000 wr)
```

O **D refs** é o total de acessos a dados (cargs + escritas). A taxa de miss seria: (40.730.582 / 89.539.191) equivalendo aproximadamente 45.5%, sendo que 40.730.582 equivale ao total de misses e 89.539.191 equivale ao total de acessos a dados.