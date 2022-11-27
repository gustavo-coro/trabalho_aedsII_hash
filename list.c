#include <stdlib.h>
#include <stdio.h>
#include "list.h"

void startList (list* l) {
    node* f;
    f = (node*) malloc(sizeof(node));
    f->data = NULL;
    f->next = NULL;
    f->before = NULL;
    l->first = f;
    l->last = f;
    l->size = 0;
}

void addItem (list* l, node item) {
    node* f;
    f = (node*) malloc(sizeof(node));
    *f = item;
    f->next = NULL;
    f->before = l->last;
    l->last->next = f;
    l->last = f;
    l->size ++;
}

void deleteItem (list* l, int index) {
    node* temp;
    if (index >= l->size/2) {
        temp = l->last;
        for (int i=l->size; i>0; i--) {
            if (i == index) {
                temp->before->next = temp->next;
                if(l->last == temp) {
                    l->last = temp->before;
                } else {
                    temp->next->before = temp->before;
                }
                l->size--;
                free(temp);
                return;
            }
            temp = temp->before;
        }
    } else {
        temp = l->first->next;
        for (int i = 1; i<l->size; i++) {
            if (i == index) {
                temp->before->next = temp->next;
                if(l->last == temp) {
                    l->last = temp->before;
                } else {
                    temp->next->before = temp->before;
                }
                l->size--;
                free(temp);
                return;
            }
            temp = temp->next;
        }
    } 
    printf("\nErro! Posicao nao existe na lista!\n");
}

int sizeList (list* l) {
    return l->size;
}

node* getItem (list* l, int index) {
    node* temp;
    if (index >= l->size/2) {
        temp = l->last;
        for (int i=l->size; i>0; i--) {
            if (i == index) {
                return temp;
            }
            temp = temp->before;
        }
    } else {
        temp = l->first->next;
        for (int i = 1; i<l->size; i++) {
            if (i == index) {
                return temp;
            }
            temp = temp->next;
        }
    } 
    printf("\nErro! Posicao nao existe na lista!\n");
}

void updateItem (list* l, int index, node* item) {
    node* temp;
    if (index >= l->size/2) {
        temp = l->last;
        for (int i=l->size; i>0; i--) {
            if (i == index) {
                temp->data = item->data;
                return;
            }
            temp = temp->before;
        }
    } else {
        temp = l->first->next;
        for (int i = 1; i<l->size; i++) {
            if (i == index) {
                temp->data = item->data;
                return;
            }
            temp = temp->next;
        }
    } 
    printf("\nErro! Posicao nao existe na lista!\n");
}

void clearList (list* l) {
    l->last = l->first;
    l->size = 0;
}

int isListEmpty(list* l) {
    if (l->first == l->last) {
        return 1;
    }
    return 0;
}