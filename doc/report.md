# Relatório referente à relização do Trabalho Prático 2

Esse documento tem como objetivo apresentar as conclusões do grupo em relação à diferença de desempenho entre os seguintes algoritmos de escalonamento, no Nanvix: Round-Robin e Fila de Prioridades.

## Idealização do novo algoritmo de escalonamento

O novo algoritmo construído baseia-se na ideia de que quanto menor o valor numérico atribuído à prioridade, maior a prioridade para que o processo seja executado. O valor total dessa prioridade é obtido por meio de um cálculo pelos valores das variáveis Counter, Priority e Nice atribuídos ao processo em questão:

> Prioridade Real = Priority + Nice + (-Counter)

Essa "fórmula" foi construída pensando-se no seguinte preceito: enquanto os valores de Priority e Nice, quando menores, representam uma prioridade maior em relação ao projeto, o valor de Counter segue a ideia contrária. Quanto maior o valor de Counter, mais essa variável aumenta a prioridade do processo ao qual ela está relacionada.

## O que são essas variáveis de prioridade?

- Counter: é o valor que indica há quanto tempo um processo está esperando na fila para ser executado.
- Priority: é o valor que indica a prioridade absoluta de um processo. Quanto menor o priority, maior é a prioridade do processo. O priority é calculado pelo sistema operacional, levando em conta o nice e outros fatores, como o tempo de espera e o tipo de processo.
- Nice: é o valor que indica a prioridade relativa de um processo. Quanto maior o nice, menor é a prioridade do processo. O nice pode ser ajustado pelo usuário ou pelo sistema operacional, de acordo com critérios de otimização.

Sabendo-se que a ideia do grupo foi obter um novo valor que, quanto menor ele for, representa uma prioridade maior para o processo, torna-se incoerente obter esse valor por meio de uma soma crua de todos esses três valores. Como o Counter atribui ao processo uma prioridade maior quando seu valor é maior, isso seria um problema na "fórmula" pois cenários como o seguinte poderiam acontecer: 

> Um processo com alto valor Counter e valores pequenos de Nice e Priority (esses últimos mostrando ao Nanvix que o tal processo deveria ter alta prioridade de execução) poderia ser executado depois de um processo com valor de Counter bem menor e valores maiores de Nice e Priority do que o suposto processo anteriormente citado.

O cenário descrito não é ideal. Para resolver esse problema, a "fórmula" criada possui o valor de Counter com o seu sinal invertido. Dessa maneira, não haverá inconsistência na decisão de prioridades por parte do Sistema Operacional. Utilizando essa ideia, em todos os casos   o processo que possui o menor valor de "Prioridade Real" terá uma prioridade maior.

## 1. Resultados de tempo utilizando o escalonador padrão do Nanvix (Round-Robin)

Resultado dos testes com o programa: `test sched`

Espera por filhos: 0 ms
Prioridades dinâmicas: 700 ms
Stress no escalonador: 0 ms

O tempo total no teste realizado foi de 700 ms


## 2. Resultados de tempo utilizando o novo escalonador (Fila de Prioridades)

Resultado dos testes com o programa: `test sched`

Espera por filhos: 0 ms
Prioridades dinâmicas: 400 ms
Stress no escalonador: 0 ms

O tempo total no teste realizado foi de 400 ms

## Conclusão

Como os tempos obtidos nos testes nos dois cenários podemos constatar uma diferença de desempenho entre as formas de se escalonar. Ao utilizar o Round-Robin, obteve-se um desempenho pior em relação a Fila de Prioridades. Essa melhora de desempenho se deve ao fato de que a Fila de Prioridades executa mais comparações para definir qual processo é mais prioritário. O ponto é que a Fila de Prioridades garante haver uma justiça mais sólida em determinar a ordem de execução dos processos, pois na Fila de Prioridades garantimos que o sistema vai considerar as três variáveis no escalonamento. Essa garantia nas prioridades gerencia melhor o tempo no escalonamento, fazendo o custo de comparações maior compensar com a gerência no escalonamento.

# Relatório referente à relização do Trabalho Prático 3: Semáforos no Nanvix

## Importância dos semáforos

Os semáforos são frequentemente utilizados para evitar condições de corrida, nas quais múltiplos processos ou threads podem acessar simultaneamente um recurso compartilhado.

## Como o foi feita a implementação do semáforo

Foi criada uma estrutura (no arquivo include/sys/sem.h) para agrupar os dados dos semáforos. Essa estrutura contém:

- Id do semáforo
- Posição do semáforo na tabela de semáforos associados aos processos
- Key (chave) do semáforo
- Valor armazenado pelo semáforo
- Estado
- Processos utilizando o semáforo

Foi definida, por meio de um DEFINE, o número máximo de semáforos do sistema.

>(sem_max, no arquivo include/nanvix/config.h)

## Tabela de semáforos associados ao processo

A tabela consiste na implementação de um vetor de valores inteiros de 16 bits, nos quais cada bit equivale a um semáforo:

- O valor 1 representa semáforos associados ao processo
- O valor 0 represneta semáforos não associados.

## Operações up e down (semop.c)

Tanto a operação up, quanto a operação down, buscam, na tabela de semáforos, o semáforo com o id correspondente ao id recebido como parâmetro. Após a busca, são realizadas as operações de sleep ou wake up.

## Criação e associação de semáforos (semget.c)

- A função create_semaphore é resposável por criar o semáforo e inicializar os valores de suas variáveis / dados.
- A função associate_semaphore recebe um endereço de um semáforo como parâmetro e realiza, através de operações com bits, o setting do valor 1 na posição referente ao semáforo na tabela de semáforos associados ao processo.

## Operações no semáforo (semctl.c)

- Função getval: retorna o valor atual so semáforo
- Função setval: define o valor do semáforo como sendo o valor da variável val, recebida como parâmetro
- Função ipc_rmid: diminui o valor da variável procusing e destrói o semáforo caso o valor resultante seja 0 
