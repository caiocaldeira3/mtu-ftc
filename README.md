# Máquina de Turing Universal

## Proposta
Partindo da proposta de um trabalho de FTC, onde deveríamos implementar uma Máquina de Turing Universal (MTU), este código tem como objetivo receber uma linguagem e identificar, a partir da informação sobre uma outra Máquina e uma palavra, se uma palavra pertence ou não à linguagem da máquina.

## Descrição de Entrada
A entrada do programa se dá na forma de uma string de seguinte estrutura:

> R<M>000R<w>

Onde M representa a Máquina de Turing a ser simulada e w a palavra que buscamos identificar pertencimento.
R<M> por conseguinte possui a seguinte estrutura:

> R<EF>00<T1>00<T2>00...<Tn>00
Onde R<EF> representam os estados finais, separados por 0, e R<Ti> representam as regras de transição de nossa máquina.

Por fim, R<Ti> possui a seguinte configuração:

> R<Ei>0R<ai>0R<Ef>0R<af>0R<D>
Onde R<Ei> e R<Ef> representam o estado inicial e o estado após escrita respectivamente, R<ai> e R<af> representam as strings da palavra inicial e após escrita respectivamente e R<D> representa a direção para onde andaremos na nossa palavra, atualmente "1" uma posição para direita e qualquer outro valor uma posição para esquerda.

## Execução

> make  
>> Compila o código

> make run  
>> Compila o código e roda o programa, aceitando strings pelo terminal.

> make run-tests  
>> Roda o programa, aceitando strings pelo terminal.

> make clean  
>> Limpa executáveis e resuldados de testes do repositório.

Ambos ```make run``` e ```make run-tests``` aceitam como argumenta ARGS="nome_do_arquivo", caso seja do interesse criar arquivos de teste.

Por fim, disponibilizei o script *run_tests.sh*, que, por padrão roda os 10 primeiros testes salvando seus resultados em output/, mas que pode ser estendido a partir da edição do script a medida que novos testes são adicionados.


## Futuras modificações
Alterar as bibliotecas de include do C++ para que seja incluído apenas o necessário, reduzindo tempo de compilação.
Alterar as estruturas de dados utilizadas nas Fitas de vector para deque, dado que queremos inserir elementos tanto na última como na primeira posição.
Alterar o armazenamento das regras de transição de vectors para unordered_map (talvez uma Trie) onde a chave é o prefixo da transição e o valor o sufixo.
Adaptar os retornos e entradas das funções, principalmente construtores, para fora do escopo do trabalho.
