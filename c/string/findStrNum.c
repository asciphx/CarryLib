#include<stdio.h>
int a,i,L,l;char b[999],c[999];;
int main(){
  scanf("%[^\n]s",&c);getchar();
  scanf("%[^\n]s",&b);getchar();
  while(b[++L]);
  while(c[l]){
    if(c[l]!=b[i++])i=0;
    if(i==L){++a;i=0;l-=L-1;}
    ++l;
  }
  printf("%d",a);
  return 0;
}