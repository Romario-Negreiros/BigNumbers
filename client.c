#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bigNumber.h"
#include "bigNumberUtils.h"

int main(void) {
    while (1) {
        BigNumber a = getBigNumber();
        BigNumber b = getBigNumber();
        char operation;

        scanf("%c", &operation);
        getchar();

        switch (operation) {
            case '+':
                printBigNumber(sumBigNumber(a, b));
                break;
            case '-':
                printBigNumber(subtractBigNumber(a, b));
                break;
            case '*':
                multiplyBigNumber(a, b);
                break;
            default:
                exit(1);
                break;
        }

        destroyBigNumber(a);
        destroyBigNumber(b);
    }
    return 0;
}
