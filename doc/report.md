# Relatório referente à relização do Trabalho Prático 2

Esse documento tem como objetivo apresentar as conclusões do grupo em relação à diferença de desempenho entre os seguintes algoritmos de escalonamento, no Nanvix: Round-Robin e Fila de Prioridades.

## Idealização do novo algoritmo de escalonamento

O novo algoritmo construído baseia-se na ideia de que quanto menor o valor numérico atribuído à prioridade, maior a prioridade para que o processo seja executado. O valor total dessa prioridade é obtido por meio de um cálculo pelos valores das variáveis Counter, Priority e Nice atribuídos ao processo em questão:

> Prioridade Real = Priority + Nice + (-Counter)

Essa "fórmula" foi construída pensando-se no seguinte preceito: enquanto os valores de Priority e Nice, quando menores, representam uma prioridade maior em relação ao projeto, o valor de Counter segue a ideia contrária. Quanto maior o valor de Counter, mais essa variável aumenta a prioridade do processo ao qual ela está relacionada.

Sabendo-se que a ideia do grupo foi obter um novo valor que, quanto menor ele for, representa uma prioridade maior para o processo, torna-se incoerente obter esse valor por meio de uma soma crua de todos esses três valores. Como o Counter atribui ao processo uma prioridade maior quando seu valor é maior, isso seria um problema na "fórmula" pois cenários como o seguinte poderiam acontecer: 

> Um processo com alto valor Counter e valores pequenos de Nice e Priority (esses últimos mostrando ao Nanvix que o tal processo deveria ter alta prioridade de execução) poderia ser executado depois de um processo com valor de Counter bem menor e valores maiores de Nice e Priority do que o suposto processo anteriormente citado.

O cenário descrito não é ideal. Para resolver esse problema, a "fórmula" criada possui o valor de Counter com o seu sinal invertido. Dessa maneira, não haverá inconsistência na decisão de prioridades por parte do Sistema Operacional. Utilizando essa ideia, em todos os casos   o processo que possui o menor valor de "Prioridade Real" terá uma prioridade maior.

## 1. Resultados de tempo utilizando o escalonador padrão do Nanvix (Round-Robin)



## 2. Resultados de tempo utilizando o novo escalonador (Fila de Prioridades)

## Conclusão

Como os tempos obtidos nos testes nos dois cenários podemos constatar uma diferença de desempenho entre as formas de se escalonar. Ao utilizar o Round-Robin, obteve-se um desempenho melhor em relação a Fila de Prioridades. Essa melhora de desempenho se deve ao fato de que a Fila de Prioridades executa mais comparações para definir qual processo é mais prioritário. O ponto positivo da Fila de Prioridades é a garantia de haver uma justiça mais sólida em determinar a ordem de execução dos processos, pois na Fila de Prioridades garantimos que o sistema vai considerar as três variáveis no escalonamento. 
