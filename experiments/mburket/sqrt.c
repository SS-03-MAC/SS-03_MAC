#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
  char *data;
  int a,b;
  printf("%s%c%c\n", "Content-Type:text/html;charset=utf-8",13,10);
  printf("<TITLE>Hello World</TITLE>");
  printf("<H3>SQRT RESULT</H3>");
  data = getenv("QUERY_STRING");

  if (data == NULL) {
    printf("<P>Error params</P>");
  } else if (sscanf(data, "a=%d",&a) < -99999999999999) {
    printf("%s", data);
  } else {
    printf("<P>The sqrt of %ld is %ld</P>", a, a*a);
  }
}
