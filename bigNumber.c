#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bigNumber.h"
#include "bigNumberUtils.h"
#include "manageMemory.h"

/**
 * @brief Lê entrada de dados, cria o BigNumber e inicializa seu vetor de elementos e propriedades de controle
 * @return O BigNumber criado
 **/
BigNumber getBigNumber() {
    BigNumber a = malloc(sizeof(struct big));
    char *elements = malloc(MAX_ARRAY_SIZE * sizeof(char));

    if (a == NULL || elements == NULL) {
        printf("Erro: Limite de memoria excedido!");
        exit(1);
    }

    if (fgets(elements, MAX_ARRAY_SIZE, stdin) == NULL) {
        free(elements);
        free(a);
        exit(1);
    };

    if (elements[0] == '-') {
        a->isNegative = 1;
        a->size--;
    } else {
        a->isNegative = 0;
    }

    a->size = strlen(elements) - 1;
    if (elements[a->size - 1] == '\n') {
        a->size = a->size - 1;
    }

    elements = realloc(elements, strlen(elements) * sizeof(char));
    a->elements = calloc(a->size + 1, sizeof(int));

    if (a->elements == NULL) {
        printf("Erro: Limite de memoria excedido!");
        exit(1);
    }


    copyElementsToBigNumber(a, elements);
    free(elements);

    return a;
}

/**
 * @brief Soma dois BigNumbers, guardando o resultado no BigNumber de maior tamanho
 * @param a Primeiro BigNumber
 * @param b Segundo BigNumber
 * @return O BigNumber de maior tamanho com o resultado 
**/
BigNumber sumBigNumber(BigNumber a, BigNumber b) {
    int size = a->realSize > b->realSize ? a->realSize : b->realSize;
    int incrementInNextSum = 0;
    int result = 0;
    char longestBigNumber = a->realSize > b->realSize ? 'a' : 'b';

    b->elements = realloc(b->elements, sizeof(int) * (b->realSize + 1));
    b->elements[b->realSize] = 0;
    a->elements = realloc(a->elements, sizeof(int) * (a->realSize + 1));
    a->elements[a->realSize] = 0;

    if (a->isNegative == b->isNegative) {
        reverseBigNumber(a);
        reverseBigNumber(b);

        for (int i = 0; i < size + 1; i++) {
            if (i > (a->realSize > b->realSize ? b->realSize : a->realSize)) {
                if (longestBigNumber == 'a') {
                    result = a->elements[i] + 0 + incrementInNextSum;
                } else {
                    result = 0 + b->elements[i] + incrementInNextSum;
                }
            } else {
                result = a->elements[i] + b->elements[i] + incrementInNextSum;
            }
            if (result > 9) {
                if (i == size - 1) {
                    if (longestBigNumber == 'a') a->realSize++;
                    else b->realSize++;
                }
                if (longestBigNumber == 'a') a->elements[i] = result % 10;
                else b->elements[i] = result % 10;
                incrementInNextSum = 1;
            } else {
                if (longestBigNumber == 'a') a->elements[i] = result;
                else b->elements[i] = result;
                incrementInNextSum = 0;
            }
        }

        reverseBigNumber(a);
        reverseBigNumber(b);

        if (longestBigNumber == 'a') return a;
        return b;
    } else {
        if (a->isNegative == 0) { // (+a) + (-b) = (+a) - (+b)
            b->isNegative = 0;
            return subtractBigNumber(a, b);
        } else {  // (-a) + (+b) = (+b) + (-a) = (+b) - (+a)
            a->isNegative = 0;
            return subtractBigNumber(b, a);
        }
    }
}

/**
 * @brief Subtrai dois BigNumbers positivos e guarda o resultado no BigNumber de maior tamanho
 * @param a BigNumber de maior tamanho
 * @param b BigNumber de menor tamanho
 * @return Sempre o BigNumber a, de maior tamanho, com o resultado
**/
BigNumber subtractPositiveBigNumbers(BigNumber a, BigNumber b) {
    reverseBigNumber(a);
    reverseBigNumber(b);

    int elementOfB = 0;
    for (int i = 0; i < a->realSize; i++) {
        if (i >= b->realSize) {
            elementOfB = 0;
        } else {
            elementOfB = b->elements[i];
        }
        if (a->elements[i] < elementOfB) {
            a->elements[i + 1] = a->elements[i + 1] - 1;
            a->elements[i] = a->elements[i] + 10 - elementOfB;
        } else {
            a->elements[i] = a->elements[i] - elementOfB;
        }
    }

    reverseBigNumber(a);
    reverseBigNumber(b);

    return a;
}

/**
 * @brief Subtrai dois BigNumbers, agindo de acordo com a combinação de sinais, salvando o resultado no maior BigNumber
 * @param a Primeiro BigNumber
 * @param b SegundoBigNumber
 * @return BigNumber de maior tamanho com o resultado
**/
BigNumber subtractBigNumber(BigNumber a, BigNumber b) {
    // (-a) - (+b) = (-a) + (-b)
    if (a->isNegative == 1 && b->isNegative == 0) {
        b->isNegative = 1;
        return sumBigNumber(a, b);
    }
    // (+a) - (-b) = (+a) + (+b)
    if (a->isNegative == 0 && b->isNegative == 1) {
        b->isNegative = 0;
        return sumBigNumber(a, b);
    }

    if (a->isNegative == 0 && b->isNegative == 0) {
        char biggerBigNumbersModule = getBiggerBigNumbersModule(a, b);
        if (biggerBigNumbersModule == 'i') {
            a->elements[0] = 0;
            a->realSize = 1;
            a->isNegative = 0;
            return a;
        } else if (biggerBigNumbersModule == 'a') {
            return subtractPositiveBigNumbers(a, b);
        } else {
            b->isNegative = 1;
            return subtractPositiveBigNumbers(b, a);
        }
    }

    // (-a) - (-b) = (-a) + (+b)
    b->isNegative = 0;
    return sumBigNumber(a, b);
}

/**
 * @brief Multiplica dois BigNumbers usando o algoritmo de karatsuba
 * @param u Primeiro BigNumber
 * @param v Segundo BigNumber
 * @param n Tamanho máximo do resultado da multiplicação
 * @return Novo BigNumber com o resultado 
**/
BigNumber karatsuba(BigNumber u, BigNumber v, int n) {
    if (u->realSize != v->realSize) {
        n = u->realSize > v->realSize ? u->realSize : v->realSize;
        resizeBigNumber(u->realSize > v->realSize ? v : u, n, 1);
    }

    BigNumber result = malloc(sizeof(struct big));
    result->elements = calloc(2 * n, sizeof(int));
    result->realSize = 0;
    result->isNegative = 0;
    addPointerBig(result);

    if (n <= 3) {
        int bigNumberU = convertToInteger(u->elements, u->realSize);
        int bigNumberV = convertToInteger(v->elements, v->realSize);
        int res = bigNumberU * bigNumberV;
        if (res == 0) {
            result->elements = realloc(result->elements, sizeof(int));
            result->elements[0] = 0;
            result->realSize = 1;
            return result;
        }
        int resultSize = (int)log10(res) + 1;

        result->elements = realloc(result->elements, resultSize * sizeof(int));
        for (int i = resultSize - 1; i > -1; i--) {
            if (res == 0) break;
            result->elements[i] = res % 10;
            res = res / 10;
        }

        result->realSize = resultSize;

        return result;
    }

    int m = n / 2;
    if (n % 2 != 0) {
        n = n + 1;
        resizeBigNumber(u, n, 1);
        resizeBigNumber(v, n, 1);
        m = n / 2;
    }

    // p = u / 10^m
    BigNumber p = malloc(sizeof(struct big));
    p->elements = calloc(m, sizeof(int));
    if (p == NULL || p->elements == NULL) {
        printf("Limite de memoria excedido!");
        exit(1);
    }
    p->realSize = m;
    p->isNegative = 0;
    p->size = m;
    for (int i = 0; i < m; i++) {
        p->elements[i] = u->elements[i];
    }

    // q = u % 10^m
    BigNumber q = malloc(sizeof(struct big));
    q->elements = calloc(m, sizeof(int));
    if (q == NULL || q->elements == NULL) {
        printf("Limite de memoria excedido!");
        exit(1);
    }
    q->realSize = m;
    q->isNegative = 0;
    q->size = m;
    for (int i = m; i < n; i++) {
        q->elements[i - m] = u->elements[i];
    }

    // r = v / 10^m
    BigNumber r = malloc(sizeof(struct big));
    r->elements = calloc(m, sizeof(int));
    if (r == NULL || r->elements == NULL) {
        printf("Limite de memoria excedido!");
        exit(1);
    }
    r->realSize = m;
    r->isNegative = 0;
    r->size = m;
    for (int i = 0; i < m; i++) {
        r->elements[i] = v->elements[i];
    }

    // s = v % 10^m
    BigNumber s = malloc(sizeof(struct big));
    s->elements = calloc(m, sizeof(int));
    if (s == NULL || s->elements == NULL) {
        printf("Limite de memoria excedido!");
        exit(1);
    }
    s->realSize = m;
    s->isNegative = 0;
    s->size = m;
    for (int i = m; i < n; i++) {
        s->elements[i - m] = v->elements[i];
    }

    BigNumber pr = karatsuba(p, r, m);
    BigNumber qs = karatsuba(q, s, m);
    BigNumber y = karatsuba(sumBigNumber(p, q), sumBigNumber(r, s), m);

    destroyBigNumber(p);
    destroyBigNumber(r);
    destroyBigNumber(q);
    destroyBigNumber(s);

    BigNumber temp = malloc(sizeof(struct big));
    if (pr->realSize > qs->realSize) {
        temp->elements = calloc(pr->realSize, sizeof(int));
        for (int i = 0; i < pr->realSize; i++) {
            temp->elements[i] = pr->elements[i];
        }
        temp->isNegative = pr->isNegative;
        temp->realSize = pr->realSize;
        temp->size = pr->size;
        BigNumber z = subtractBigNumber(y, sumBigNumber(pr, qs));
        resizeBigNumber(z, z->realSize + m, 0);
        BigNumber pr10 = temp;
        resizeBigNumber(pr10, temp->realSize + 2 * m, 0);
        BigNumber pr10z = sumBigNumber(pr10, z);
        result = sumBigNumber(pr10z, qs);
        addPointerBig(temp);
    } else {
        temp->elements = calloc(qs->realSize, sizeof(int));
        for (int i = 0; i < qs->realSize; i++) {
            temp->elements[i] = qs->elements[i];
        }
        temp->isNegative = qs->isNegative;
        temp->realSize = qs->realSize;
        temp->size = qs->size;
        BigNumber z = subtractBigNumber(y, sumBigNumber(pr, qs));
        resizeBigNumber(z, z->realSize + m, 0);
        BigNumber pr10 = pr;
        resizeBigNumber(pr10, pr->realSize + 2 * m, 0);
        BigNumber pr10z = sumBigNumber(pr10, z);
        result = sumBigNumber(pr10z, temp);
        addPointerBig(temp);
    }

    return result;
}

/***
 * @brief Função de controle pra multiplicação de dois BigNumbers: define o tamanho máximo do resultado,
 * @brief redimensiona os BigNumbers para terem o mesmo tamanho e determina o sinal do resultado
 * @param u Primeiro BigNumber
 * @param v Segundo BigNumber
**/
void multiplyBigNumber(BigNumber u, BigNumber v) {
    int n = u->realSize;
    int signal;
    if (u->realSize != v->realSize) {
        n = u->realSize > v->realSize ? u->realSize : v->realSize;
        resizeBigNumber(u->realSize > v->realSize ? v : u, n, 1);
    }

    BigNumber result;
    if (u->isNegative == v->isNegative)
        signal = 0;
    else
        signal = 1;
    result = karatsuba(u, v, n);
    result->isNegative = signal;
    printBigNumber(result);

    addBigPointers();
    freePointers();
    freePointersBig();
}