# Representação do BigNumber

O BigNumber foi representado através de uma struct chamada big, que contém as seguintes propriedades:

- int* elements: vetor de inteiros, que contém os digitos do BigNumber, foi utilizado inteiros ao invés de caractéres para eliminar a necessidade de conversão quando realizada operações matemáticas com os elementos.
- int isNegative: Propriedade de controle para saber se o BigNumber é ou não negativo, se sim, ela assume valor 1, se não, 0.
- int size: Propriedade de controle para saber o tamanho total do número após ser retirado da entrada, contando zeros a esquerda e sinal de '-'.
- int realSize: Propriedade de controle para saber o tamanho real do BigNumber, desconsiderando zeros a esquerda e sinal de '-'.

# Interface pública do tipo BigNumber

```
    typedef struct big {
        int *elements;
        int isNegative;
        int size;
        int realSize;
    } *BigNumber;
```

# Algoritmos utilizados

- [Algoritmo de Karatubsa](https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/karatsuba.html): Ultilizado na implementação do método para multiplicar dois BigNumbers.
