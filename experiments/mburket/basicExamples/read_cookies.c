#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char *data;
  printf("%s%c%c\n", "Content-Type:text/html;charset=utf-8",13,10);
  printf("%s",getenv("HTTP_COOKIE"));
  }