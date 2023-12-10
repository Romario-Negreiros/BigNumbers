#ifndef MANAGEEMORY_H
#define MANAGEMEMORY_H

#include "bigNumber.h"

struct Node {
  int *data;
  struct Node* next;
};

struct NodeBig {
  BigNumber data;
  struct NodeBig* next;
};

void addPointerBig(BigNumber ptr);

void addBigPointers();

void freePointers();

void freePointersBig();

#endif