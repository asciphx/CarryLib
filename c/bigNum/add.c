#include<stdio.h>
#include<stdlib.h>
char*bigAdd(const char*m,const char*n){
  if(m[0]==0||n[0]==0)return NULL;
  int i=0,l=0,z=0,x,y;
  char*j=(char*)calloc(999,sizeof(char));
  while(m[++i]);while(n[++l]);y=x=i>l?i:l;
  while(y>z){
    if(i)j[y]+=m[--i];if(l)j[y]+=n[--l];
    if(j[y]>0x69){
      j[y-1]+=1;j[y]%=0x3a;
      if(y==1)j[0]=0x31,--z;
    }else if(j[y]>0x5f){
      j[y]-=0x30;
    }else if(j[y]>0x39){
      j[0]=0x31,--z;j[y]-=0xa;
    }--y;
  }
  if(!z){while(i<x)j[i]=j[i+1],++i;j[i]=0;}
  return j;
}
int main(){
  char m[998],n[998];scanf("%s %s",m,n);
  char*r=bigAdd(m,n);printf("%s",r);
  // char*r=BigPlus("","");printf("%d",r==NULL);
  free(r);return 0;
}