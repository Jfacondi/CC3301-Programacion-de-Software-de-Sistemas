S#include <stdio.h>
#include <stdlib.h>

#include "elim-rango.h"

void eliminarRango(Nodo **phead, double y, double z) {
  Nodo *head = *phead;
  Nodo *prev = NULL;

  while (head != NULL && head->x <= z) {
    if (head->x >= y && head->x <= z) {
        Nodo *temp = head;
        if (prev == NULL) {
            *phead = head->prox;
        }
        else {
            prev->prox = head->prox;
        }
        head = head->prox;
        free(temp);
    }
    else {
        prev = head;
        head = head->prox;
        }
    }
}
