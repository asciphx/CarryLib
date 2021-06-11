#include<stdio.h>
#include<stdlib.h>
int gt(const char*a,const char*b,int l){
  int l1=strLen(a)-1,l2=strLen(b);
  if(l1>l2)return 1;else if(l1<l2)return 0;
  for(int i=l,j=0;j<l2;--i,++j){
    if(a[i]==b[j])continue;return a[i]>b[j];
  }return 1;
}
char*bigDiv(const char*m,const char*n){
  if(m[0]==0||n[0]==0)return NULL;
  int i=0,l=0,z,x,y;
  char r[200]={0},*j=(char*)calloc(999,sizeof(char));
  while(m[++i]);while(n[++l]);z=i+l-1;
  return j;
}
//To be continued
int main(){
  char m[100],n[100];scanf("%s %s",&m,&n);
  char*r=bigDiv(m,n);printf("%s",r);free(r);
  return 0;
}