#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bigNumberUtils.h"
#include "bigNumber.h"

/**
 * @brief Verifica se o vetor de caractéres da entrada é composto apenas por digitos (0-9) e/ou um prefixo '-'
 * @param elements Vetor a ser validados
 * @return Retorna 0 se o vetor é inválido, ou 1, se o vetor for válido
**/
int validateBigNumber(char *elements) {
    int size = strlen(elements);
    for (int i = 0; i < size; i++) {
        if (elements[i] == '\0') continue;
        if (elements[i] == '\n') continue;

        if ((elements[i] < 48 || elements[i] > 57) && elements[i] != 45) {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Copia os elementos de um vetor de caractéres em uma propriedade do tipo vetor de inteiros no BigNumber
 * @param a BigNumber de destino dos elementos
 * @param elements Elementos a serem copiados no BigNumber
**/
void copyElementsToBigNumber(BigNumber a, char *elements) {
    int skips = 0;
    int temp = 0;
    for (int i = 0; i < a->size; i++) {
        if (elements[i] == '-') continue;
        if (elements[i] == '0' && temp == 0) {
            skips++;
            continue;
        } else
            temp = 1;

        if (a->isNegative == 1) {
            a->elements[i - 1 - skips] = elements[i] - '0';
        } else {
            a->elements[i - skips] = elements[i] - '0';
        }
    }
    if (a->isNegative == 1) {
        a->realSize = a->size - skips - 1;
    } else
        a->realSize = (a->size - skips);
    if (a->realSize == 0) {
        a->realSize++;
        a->isNegative = 0;
    }
}

/**
 * @brief Inverte a ordem dos elementos de um BigNumber
 * @param a BigNumber para inverter a ordem
**/
void reverseBigNumber(BigNumber a) {
    for (int i = 0; i < a->realSize / 2; i++) {
        int temp = a->elements[i];
        a->elements[i] = a->elements[a->realSize - i - 1];
        a->elements[a->realSize - i - 1] = temp;
    }
}

/**
 * @brief Imprime no terminal os elementos do BigNumber
 * @param a BigNumber para imprimir
**/
void printBigNumber(BigNumber a) {
    int temp = 0;
    if (a->isNegative == 1) {
        printf("-");
    }
    for (int i = 0; i < a->realSize; i++) {
        if (temp == 0 && a->elements[i] == 0) continue;
        temp = 1;
        printf("%d", a->elements[i]);
    }
    if (temp == 0 && a->elements[0] == 0) {
        printf("%d", a->elements[0]);
    };
    printf("\n");
}

/**
 * @brief Libera a memória ocupada por um BigNumber e seus elementos
 * @param a BigNumber para ser desalocado da memória
**/
void destroyBigNumber(BigNumber a) {
    free(a->elements);
    free(a);
}

/**
 * @brief Determina o maior módulo entre dois BigNumbers
 * @param a Primeiro BigNumber
 * @param b Segundo BigNumber
 * @return Retorna 'i' se os BigNumbers são iguais, 'a' se o BigNumber a é o maior ou 'b' se o BigNumber b é o maior
**/
char getBiggerBigNumbersModule(BigNumber a, BigNumber b) {
    if (a->realSize == b->realSize) {
        for (int i = 0; i < a->realSize; i++) {
            if (a->elements[i] > b->elements[i]) {
                return 'a';
            } else if (a->elements[i] < b->elements[i]) {
                return 'b';
            }
        }

        return 'i';
    } else if (a->realSize > b->realSize) {
        return 'a';
    } else {
        return 'b';
    }
}

/**
 * @brief Altera o tamanho do BigNumber, realocando memória e preenchendo os espaços vázios, se houver
 * @param a BigNumber para alterar o tamanho
 * @param n Novo tamanho do BigNumber
 * @param shiftZerosToLeft Flag para controlar se os zeros serão adicionados na esquerda (início) ou na direita (fim) do BigNumber
**/
void resizeBigNumber(BigNumber a, int n, int shiftZerosToLeft) {
    a->elements = realloc(a->elements, n * sizeof(int));
    if (shiftZerosToLeft == 1) {
        for (int i = 0; i < a->realSize; i++) {
            a->elements[n - i - 1] = a->elements[a->realSize - i - 1];
        }
        for (int i = 0; i < n - a->realSize; i++) a->elements[i] = 0;
    } else {
        for (int i = a->realSize; i < n; i++) a->elements[i] = 0;
    }
    a->realSize = n;
}

/***
 * @brief Converte um vetor de inteiros em um inteiro
 * @param a Ponteiro pra um vetor de inteiros
 * @param n Tamanho do vetor
 * @return Inteiro obtido a partir do vetor 
**/
int convertToInteger(int *a, int n) {
    int x = 0;
    for (int i = 0; i < n; i++) {
        x = x * 10 + a[i];
    }
    return x;
}