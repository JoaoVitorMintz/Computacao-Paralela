# Conteúdo estudado

## Relacionando a teoria à prática deste laboratório

O OpenMP oferece um controle muito fino sobre como o parallel for pode ser usado para divisão de trabalho, principalmente quando é necessário a distribuição de carga para balanceamento, isto é, quando as interações não têm todas o mesmo custo computacional.

## Característica do OpenMP para balanceamento:

Por padrão, o OpenMP divide interações de forma estática e equitativa. Se houver 100 iterações e 4 threads, cada tread receberá 25 iterações para trabalhar sobre, entretanto, no caso de haver iterações mais lentas, isso fará com que uma thread fique ociosa enquanto a outra ainda tenha muito trabalho. Para realizar o balanceamento, o OpenMP utiliza do **schedule** para controlar a distribuição:

 - **schedule(static, chunk)**: Divide as iterações em blocos (*chunks*) de tamanho *chunk* e as distribui de forma fixa (algoritmo round-robin) entre as threads. É previsível e tem baixo overhead.

 - **schedule(dynamic, chunk)**: As iterações em chunks são colocadas em uma "fila de trabalho". Quando uma thread termina seu chunk, ela pega o próximo disponível. Apesar de ser ótima para cargas desbalanceadas, possui maior overhead.

 - **schedule(guided)**: Começa distribuindop blocos grandes e, con forme o trabalho restante dimininui, os blocos distribuídos se tornam cada vez menores. É um bom meio-termo.

 - **schedule(auto)**: Deixa o compilador/runtime decidir a melhor estratégia.

## Paralelismo em Nível de Dados: SIMD

Outro nível de paralelismo é aquele que ocorre **dentro de um único core**.

***Analogia com supermercado:***

 - Ter vários caixas abertoes é como usar **múltiplas threads**(parallel for). Cada cauxa (core) processa um cliente (iteração) de cada vez.
 - Um caixa que usa um leitor de código de barras para escanear 4 itens de uma só vez está usando **SIMD**. É uma única instrução (escanear) aplicada a múltiplos dados (itens).

Os processadores modernos possuem unidades de hardware especiais (unidades vetoriais) que podem realizar a mesma operação em múltiplos dados de uma só vez. Isso é chamado de *SIMD* (Single Instruction, Multiple Data). Por exemplo, uma única instrução pode somar 4 pares de números simultaneamente.

A diretiva #pragma omp simd é uma dica explícita para o compilador. Com essa diretiva, **garante** que o laço não tem dependências entre iterações e que pode ser seguramente vetorizado, mesmo que o compilador não consiga provar isso sozinho.

Exemplo:

```c
#pragma omp parallel for simd
for (int i = 0; i < N; i++) {
    c[i] = a[i] + b[i]
}
```

Aqui, o parallel for divide as 'N' iterações entre as threads. Dentro de cada thread, o *simd* instrui o compilador a usar instruções SIMD para processar as itnerações atribuídas a ela em blocos, acelerando ainda mais o cálculo.

## Atividades Práticas:

### 4.1) Experimentando com Agendamentos

 - **schedule(dynamic, 1)**: cada thread recebe uma iteração por vez; maior overhead, melhor adaptação quando as iterações têm tempos diferentes.
 - **Ordem de execução**: não é garantida em dynamic e guided, então a saída aparece embaralhada mesmo quando as iterações são as mesmas.
 - **Distribuição de trabalho**: static é previsível, dynamic é reativa, guided é intermediário entre os dois.

### 4.2) Otimização de Matriz-Vetor

Para uma matriz 1000x1000:

| Agendamento | Tempo seq | Tempo par | Speedup | Vencedor  |
| ----------- | --------- | --------- | ------- | --------- |
| static,1    | 2.88s     | 0.80s     | 3.60x   | ❌        |
| dynamic,1   | 2.83s     | 0.75s     | 3.77x   | ✅        |
| guided      | 2.86s     | 0.73s     | 3.89x   | 🎯 MELHOR |

Quanto testei com uma matriz 500x500, percebi que o static havia se sobressaído, entretanto, ao aumentar o tamanho da matriz, os outros agendamentos se mostraram melhores. Isso se deve ao fato de que, para matrizes menores, o estático se sobressai pois possui menor custo de sincronização (menos overhead), entretanto, ao utilizar de uma matriz maior, o dynamic e guided se destacam já que, apesar de possuirem maior overhead, o overhead de escalonamento vira uma fração insignificante do tempo total.