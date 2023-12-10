#include <stdio.h>
#include <stdlib.h>

#include "bigNumber.h"
#include "manageMemory.h"

struct Node* head = NULL;
struct NodeBig* bigsList = NULL;

/**
 * @brief
 * @param ptr
**/
void addPointer(int *ptr) {
  if (head == NULL) {
    head = (struct Node*)malloc(sizeof(struct Node));
    head->data = ptr;
    head->next = NULL;
  } else {
    struct Node* temp = head;
    while (temp->next != NULL) {
      if (temp->data == ptr) {
        return;
      }
      temp = temp->next;
    }
    if (temp->data != ptr) {
      temp->next = (struct Node*)malloc(sizeof(struct Node));
      temp->next->data = ptr;
      temp->next->next = NULL;
    }
  }
}

/**
 * @brief
 * @param ptr
**/
void addPointerBig(BigNumber ptr) {
  if (bigsList == NULL) {
    bigsList = (struct NodeBig*)malloc(sizeof(struct NodeBig));
    bigsList->data = ptr;
    bigsList->next = NULL;
  } else {
    struct NodeBig* temp = bigsList;
    while (temp->next != NULL) {
      if (temp->data == ptr) {
        return;
      }
      temp = temp->next;
    }
    if (temp->data != ptr) {
      temp->next = (struct NodeBig*)malloc(sizeof(struct NodeBig));
      temp->next->data = ptr;
      temp->next->next = NULL;
    }
  }
}

/**
 * @brief
**/
void addBigPointers() {
  struct NodeBig* temp = bigsList;
  while (temp != NULL) {
    addPointer(temp->data->elements);
    temp = temp->next;
  }
}

/**
 * @brief
**/
void freePointers() {
  struct Node* temp = head;
  while (temp != NULL) {
    struct Node* next = temp->next;
    free(temp->data);
    free(temp);
    temp = next;
  }
  head = NULL;
}

/**
 * @brief
 * @param ptr
**/
void freePointersBig() {
  struct NodeBig* temp = bigsList;
  while (temp != NULL) {
    struct NodeBig* next = temp->next;
    free(temp->data);
    free(temp);
    temp = next;
  }
  bigsList = NULL;
}
