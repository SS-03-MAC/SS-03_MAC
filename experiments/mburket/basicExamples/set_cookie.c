#include <stdio.h>
#include <stdlib.h>

int main(void) {
  printf("Set-Cookie: NAME=Apple\n");
  printf("%s%c%c\n", "Content-Type:text/html;charset=utf-8",13,10);
  }
