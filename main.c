#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "list.h"

int main(int argc, char *argv[]) {

  //analizar se os arquivos necessarios para a execucao foram colocados
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
    //ler todos os caracteres da linha
    for (int i = 0; i < strlen(str); i++) {
      //adiciona o caracter na string se for uma letra
      //ignora numeros, caracteres especiais e separa cada palavra da linha
      if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122)) {
        if (str[i] >= 65 && str[i] <= 90) {
          //tratamento para letras maiusculas
          str[i] = str[i] + 32;
        }
        //adiciona o caracter na string
        size_t sizeWord = strlen(word);
        word[sizeWord] = str[i];
        word[sizeWord+1] = '\0';
      } else {
        //chama a funcao hash e adiciona a string na tabela
        //ignora strings vazias e com uma letra
        if ((strlen(word) > 1)) {
          //chamar o hash
          hashData* temp = (hashData*) malloc(sizeof(hashData));
          strcpy(temp->data, word);
          temp->line = lineCount;
          temp->key = stringHash(temp->data);
          insertData(temp, table);
          free(temp);
        }
        //adiciona uma linha caso chegue na quebra de linha (\n)
        if (str[i] == 10) {
          lineCount++;
        }
        //reinicia a string
        word[0] = '\0';
      }
    }
  }
  if (word[0] != '\0') {
    //chama o hash para a ultima palavra do arquivo
    hashData* temp = (hashData*) malloc(sizeof(hashData));
    strcpy(temp->data, word);
    temp->line = lineCount;
    temp->key = stringHash(temp->data);
    insertData(temp, table);
    free(temp);
  }

  //ler arquivo de saida e buscar as palavras

  str[0] = '\0';
  //le a primeira linha do arquivo com o valor numerico
  //esse valor nao sera necessario para imprimir as palavras
  size_t sizeStr;
  fgets(str, 50, arqOut);
  sizeStr = strlen(str);
  if (str[sizeStr-1] == 10) {
    str[sizeStr-1] = '\0';
  }

  while (fgets(str, 50, arqOut) != NULL) {
    //lidando com a quebra de linha
    sizeStr = strlen(str);
    if (str[sizeStr-1] == 10) {
      str[sizeStr-1] = '\0';
      sizeStr = strlen(str);
    }
    for (int i = 0; i < strlen(str); i++) {
      if (str[i] >= 65 && str[i] <= 90) {
        str[i] = str[i] + 32;
      }
    }
    /*usar uma lista para armazenar as linhas em que a palavra aparece*/
    list* lines = (list*) malloc(sizeof(list));
    startList(lines);

    int hash = stringHash(str);
    int timesText;
    findItem(table, str, hash, &timesText, lines);
    printf("%d %s ", timesText, str);
    for (int i = 1; i <= sizeList(lines); i++) {
      node* receive = (node*) malloc(sizeof(node));
      receive = getItem(lines, i);
      printf("%d ", receive->data);
      free(receive);
    }
    printf("\n");
    free(lines);
  }


  fclose(arq);
  fclose(arqOut);

  return 0;
}