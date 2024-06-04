# Philosophers

## Visão Geral
Trabalhar com threads e algo interessante afinal e uma forma de IPC, para comecamos precisamos entender o problema, e sempre bom comecamos com Parse, o que o usuario vai nos da e o que vamos fazer com essa informacao.
Na chamada do nosso progama o usuario tem que passar a quantidade de Threads, O tempo de morte do Filosofo, o tempo que ele vai comer, e o tempo que ele vai dormir e ele pode passar tambem quantas vezes o filosofo vai comer se quiser, ou seja, 

Ex ./philo [NF] [TD] [TA] [TD] [QA] , sendo o ultimo opcional.

Mas vamos ao problema, com threads nos utilizamos a mesma variavel em diferentes threads, fazendo assim consultas,alteracoes. Entao para gente nao ter race condition,temos que fazer de uma forma muito bem sincronizada, para isso
temos os mutex, de forma que o mutex bloqueia aquela variavel para thread fazer o que precisa e apos sua alteracao voce pode liberar e a outra thread ja vai enxergar aquela variavel com valor atualizado, pense como se fosse travas 
obrigando a voce esperar a alteracao ser feita para voce poder continuar. O objetivo do filosofo e todo mundo comer sendo que e necessario 2 garfos sendo que cada 1 so tem um, entao precisamos criar uma forma aonde todos possam se alimentar
de acordo com tempo passado. 

Threads podem parecer rapidas comparada a processos, mas devem ser muito bem organizadas e muito bem otimizadas para que tudo ocora bem.Afinal no nosso problema nao podemos avisar para o filosofos que um morreu, entao
criamos outra thread para monitorar nossa refeicao, ela tem como principal objetivo verificar a ultima vez que os filosofos comeram e se todo mundo ja comeu a quantidade x escolhida pelo usuario. 

### Meu monitor
![MONITOR](img/Monitor.png)

A solucao e simples utilizando a ideia do impar e par, impar faz seu garfo fica na mao esquerda e pega o garfo do colega a frente, utilizamos um usleep para que os pares comecem depois, assim evitamos data races, ou seja eles tentarem pegar o garfo ao mesmo tempo,
isso e importante, precisamos deixar-los numa sincronia aonde isso nao aconteca. 

Para nosso monitor temos duas funcoes aonde vao verificar a ultima vez que alguem comeu ou se todos ja estao sastifeitos. temos alguns spinlocks utilizados exatamente para comecar toda rotina apos 
a criacao de todos. Apos isso vamos trabalhar travando e destravando as variaveis e verificando, de forma que nenhuma tenha qualquer tipo de race contion ou data race.


![IMAGEM](img/example.png)
