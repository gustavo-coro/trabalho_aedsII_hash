#ifndef HASH_H
#define HASH_H

#include "list.h"

extern const int MAX_SIZE;
extern const int MAX_LENGTH_STR;
extern const int MAX_NUMBER_WORDS;

typedef struct hashData {
    //char* data;
    char data[21];
    int key;
    int line;
    int timesInLine;
} hashData;


void startTable (hashData*[]);
unsigned int stringHash (char*);
void insertData (hashData*, hashData*[]);
void printTable (hashData*[]);
void findItem (hashData*[], char*,int,int*,list*);

#endif