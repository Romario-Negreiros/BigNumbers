#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#define MAX_ARRAY_SIZE 999999

typedef struct big {
    int *elements;
    int isNegative;
    int size;
    int realSize;
} *BigNumber;

BigNumber getBigNumber();

BigNumber sumBigNumber(BigNumber a, BigNumber b);

BigNumber subtractBigNumber(BigNumber a, BigNumber b);

void multiplyBigNumber(BigNumber a, BigNumber b);

#endif