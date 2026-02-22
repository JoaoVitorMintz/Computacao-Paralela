# Questões para Reflexão:

1. Qual a principal diferença entre o valor da variável pid no processo pai e no processo filho,
logo após a chamada fork()? Por que essa diferença é tão importante?

```bash
R: A principal diferença no valor da variável do processo pai e do processo filho é de identificar qual é qual e, em seguida, permitir o controle lógico de execução, isto é, diferencial qual código deve ser executado pelo pai e qual deve ser executado pelo filho.
```

2. O que aconteceria no exemplo fork example.c se você removesse a linha wait(NULL);
do código do processo pai? Compile e execute para testar sua hipótese. (Pesquise sobre
"processos zumbis" e "processos órfãos" para entender o comportamento).

```bash
R: Ao remover a linha wait(NULL);, o processo pai não coleta status de término do filho. Quanto o filho termina, ele pode se tornar um processo zumbi, pois sua entrada permanece na tabela de processos até que o pai chame wait() ou termine sua execução.
```