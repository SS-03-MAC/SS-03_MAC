#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX(a,b) ((a) > (b) ? a : b)
#define MIN(a,b) ((a) < (b) ? a : b)

int main(void) {
  printf("%s\n", "Content-Type:text/html;charset=utf-8");
  char Buffer[512]={0};
  int InputLength = 0;
  printf("%s", getenv("INPUT_LENGTH"));
}
