#include <stdio.h>
#include <stdlib.h>
int main() {
  char szNumbers[] = "1000 0000000100";
  char *pEnd;
  long int li1, li2;
  li1 = strtol(szNumbers, &pEnd, 10);
  li2 = strtol(pEnd, &pEnd, 10);
  printf("%d  %d\n", li1, li2);
  if (li1 == li2) printf("=");
  if (li1 < li2) printf("<");
  if (li1 > li2) printf(">");
  return 0;
}