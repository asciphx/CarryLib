#include"c/bigNum.h"
#include"c/str.h"
#include<stdio.h>
int main(){
  char m[998],n[998];scanf("%s %s",&m,&n);
  char*r=bigAdd(m,n);printf("bigAdd: %s\n",r);free(r);
  r=bigSub(m,n);printf("bigSub: %s\n",r);free(r);
  r=bigMul(m,n);printf("bigMul: %s\n",r);free(r);
  return 0;
}