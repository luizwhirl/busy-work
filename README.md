# Busy work
## O que diabo é isso?

Busy work é um pequeno projeto, do tamanho de um nada. Consiste na execução de um programa gerador de diversas threads, quanto núcleos da CPU disponíveis; no qual cada uma faz um cálculo pesado, sem qualquer pausa.

O intuito do programa é de apenas manter todos os núcleos em uso intenso, aumentando a temperatura da CPU, e deixando o computador lento.

## Como instalar
Não vou ensinar a instalar nada, execute esse programa por sua conta e risco 😝.

Porém você vai precisar do C++11 para poder usar a biblioteca `thread`, já tendo, compile assim:

```
g++ -std=c++11 main.cpp -o busy-work -pthread
```
É importante o uso da flag `-pthread` para o suporte à threads 


Se vira aí