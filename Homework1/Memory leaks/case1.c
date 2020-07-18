// hello.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char* name = malloc(7 * sizeof(char));
  
  free(name);
  return 0;
}
