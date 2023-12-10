Nicolas Yudi Kim - 11202111134
Romario Negreiros Baldarenas Silva - 11202230894
Wesley Ramos dos Santos - 11202231389

# Representação do BigNumber

O BigNumber foi representado através de uma struct chamada big, que contém as seguintes propriedades:

- int* elements: vetor de inteiros, que contém os digitos do BigNumber, foi utilizado inteiros ao invés de caractéres para eliminar a necessidade de conversão quando realizada operações matemáticas com os elementos.
- unsigned int isNegative: Propriedade de controle para saber se o BigNumber é ou não negativo, se sim, ela assume valor 1, se não, 0.
- unsigned int size: Propriedade de controle para saber o tamanho total do número após ser retirado da entrada, contando zeros a esquerda e sinal de '-'.
- unsigned int realSize: Propriedade de controle para saber o tamanho real do BigNumber, desconsiderando zeros a esquerda e sinal de '-'.

# Interface pública do tipo BigNumber

```
    struct big {
        int *elements;
        unsigned int isNegative;
        unsigned int size;
        unsigned int realSize;
    } typedef *BigNumber;
```

# Algoritmos utilizados

- [Algoritmo de Karatubsa](https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/karatsuba.html): Ultilizado na implementação do método para multiplicar dois BigNumbers.

# Divisão de trabalhos

- Implementação dos métodos de 'utils' para o BigNumber e do código no cliente: Romario
- Implementação do método de soma e dos métodos para gerenciamento de memória: Wesley
- Implementação dos métodos de subtração: Nicolas
- Implementação do método para multiplicação: Todos os membros do grupo participaram desta implementação
- Revisão do código: Todos os membros do grupo participaram desta etapa