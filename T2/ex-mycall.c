/* 
 * Uso da nova chamada de sistema
 */ 
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int r = syscall(380); 
  printf("Retorno da chamada de sistema: %d.\n", r);
  return 0;
}
