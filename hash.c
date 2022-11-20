#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

const int MAX_SIZE = 521;
const int MAX_LENGTH_STR = 20;
const int MAX_NUMBER_WORDS = 80;

void startTable (hashData* table[]) {
    for (int i = 0; i < MAX_SIZE; i++) {
        hashData* d = (hashData*) malloc(sizeof(hashData));
        d->data[0] = '\0';
        d->key = -1;
        d->line = 0;
        d->timesInLine = 0;
        table[i] = d;
    }
}

unsigned int stringHash (char* str) {
    int cod = 0;
    unsigned int hash = 257;

    while (cod = *str++) {
      hash = hash * 33 + cod;
    }
    hash = hash%521;
    return hash;
}

void insertData (hashData* newData, hashData* table[]) {
    for (int i = newData->key; ; i++) {
        if (table[i]->key == -1) {
            //table[i]->data = newData->data;
            strcpy(table[i]->data, newData->data);
            table[i]->key = newData->key;
            table[i]->line = newData->line;
            table[i]->timesInLine = 1;
            break;
        } else if (strcmp(table[i]->data, newData->data) == 0) {
            if (table[i]->line == newData->line) {
                table[i]->timesInLine++;
                break;
            }
        }
        if (i == MAX_SIZE) {
            i = 0;
        }
    }
}

void printTable (hashData* table[]) {
    printf("\n\n-----Table-----\n\n");
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("\n%d - ", i);
        fputs(table[i]->data, stdout);
        printf(" - Hash: %d", table[i]->key);
        printf(" - Line: %d", table[i]->line);
        printf(" - Times in line: %d", table[i]->timesInLine);
    }
}

void findItem (hashData* table[], char* str, int hash, int* timesText, char* lines) {
    *timesText = 0;
    lines[0] = '\0';
    for (int i = hash; ; i++) {
        if (table[i]->key == -1) {
            return 0;
        } else if (strcmp(str, table[i]->data) == 0) {
            *timesText += table[i]->timesInLine;
            char* temp;
            sprintf(temp, "%d%s", table[i]->line, " ");
            strcat(lines,temp);
        }
    }
}