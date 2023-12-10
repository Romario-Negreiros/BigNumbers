#ifndef BIGNUMBERUTILS_H
#define BIGNUMBERUTILS_H

#include "bigNumber.h"

int validateBigNumber(char *elements);

void copyElementsToBigNumber(BigNumber a, char *elements);

void reverseBigNumber(BigNumber a);

void printBigNumber(BigNumber a);

void destroyBigNumber(BigNumber a);

char getBiggerBigNumbersModule(BigNumber a, BigNumber b);

void resizeBigNumber(BigNumber a, int n, int shiftZerosToLeft);

int convertToInteger(int *a, int n);

#endif