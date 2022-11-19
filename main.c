#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

int main(int argc, char **argv[]) {

  if (argc < 3) {
    perror("Faltam parametros. Sao necessarios 2 arquivos para executar corretamente.\n");
    return -1;
  } else if (argc > 3) {
    perror("Parametros demais. Sao necessarios somente 2 arquivos.\n");
    return -1;
  }

  FILE *arq = fopen(argv[1], "r");
  FILE *arqOut = fopen(argv[2], "r");

  if ((arq == NULL) || (arqOut == NULL)) {
    perror("Arquivo nao pode ser aberto.\n");
    return -1;
  }

  hashData* table[MAX_SIZE];
  char str[MAX_NUMBER_WORDS+1];
  char word[MAX_LENGTH_STR+1];
  word[0] = '\0';
  int lineCount = 1;

  startTable(table);

  while (fgets(str, MAX_NUMBER_WORDS+1 ,arq) != NULL) {
    for (int i = 0; i < strlen(str); i++) {
      if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122)) {
        if (str[i] >= 65 && str[i] <= 90) {
          str[i] = str[i] + 32;
        }
        size_t sizeWord = strlen(word);
        word[sizeWord] = str[i];
        word[sizeWord+1] = '\0';
      } else {
        if (word[0] != '\0') {
          //chamar o hash
          hashData* temp = (hashData*) malloc(sizeof(hashData));
          //temp->data = word;
          strcpy(temp->data, word);
          temp->line = lineCount;
          temp->key = stringHash(temp->data);
          insertData(temp, table);
          free(temp);
        }
        if (str[i] == 10) {
          lineCount++;
        }
        word[0] = '\0';
      }
    }
  }
  if (word[0] != '\0') {
    //chama o hash para a ultima palavra do arquivo
    hashData* temp = (hashData*) malloc(sizeof(hashData));
    //temp->data = word;
    strcpy(temp->data, word);
    temp->line = lineCount;
    temp->key = stringHash(temp->data);
    insertData(temp, table);
    free(temp);
  }

  //ler arquivo de saida e buscar as palavras
  str[0] = 0;
  int numberWords = 0;
  printData* dta;
  int index = 0;
  while (fgets(str, MAX_LENGTH_STR+1, arqOut) != NULL) {
    size_t sizeLine = strlen(str);
    str[sizeLine-1] = '\0';
    if ((str[0] >= 48) && (str[0] <= 57)) {
      numberWords = atoi(str);
      dta = (printData*) malloc(numberWords * sizeof(printData));
      index = -1;
    } else {
      strcpy(dta[index].data, str);
      dta[index].key = stringHash(dta[index].data);
      dta[index].lines[0] = "\0";
      dta[index].timesInText = 0;
      findItem(dta[index],table);
    }
    index++;
  }

  for (int i = 0; i < index; i++) {
    printf("\n%d ", dta[i].timesInText);
    fputs(dta[i].data, stdout);
    fputs(dta[i].lines, stdout);
    pr
  }




  fclose(arq);
  fclose(arqOut);

  return 0;
}