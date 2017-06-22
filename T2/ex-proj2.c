/* 
 * Uso da nova chamada de sistema
 */ 
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int r;

  r = syscall(381, 1, "bananinha1", 10);
  printf("Retorno da chamada de sistema: %d.\n", r);

  r = syscall(381, 20, "bananinha2", 3);
  printf("Retorno da chamada de sistema: %d.\n", r);

  r = syscall(381, 654, "bananinha3", 5);
  printf("Retorno da chamada de sistema: %d.\n", r);

  sleep(5);

  char* value;
  value = (char*) malloc(100*sizeof(char));
  syscall(382, 1, 1, value);
  printf("Valor encontrado: %s\n", value);

  value = (char*) malloc(100*sizeof(char));
  syscall(382, 20, 12, value);
  printf("Valor encontrado %s\n", value);

  value = (char*) malloc(100*sizeof(char));
  syscall(382, 654, 1, value);
  printf("Valor encontrado: %s\n", value);

  value = (char*) malloc(100*sizeof(char));
  syscall(382, 1, 1, value);
  printf("Valor encontrado: %s\n", value);

  return 0;
}

