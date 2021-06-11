#include<stdio.h>
#include<stdlib.h>
char*bigSub(const char*m,const char*n){
  if(m[0]==0||n[0]==0)return NULL;
  int i=0,l=0,x,y,f;char*j=(char*)calloc(999,sizeof(char));
  while(m[++i]);while(n[++l]);x=y=i>l?i:l;
  while(y--){ if(i)j[y]+=m[--i]-0x30;if(l)j[y]-=n[--l]-0x30; }
  while(j[++y]==0);f=j[y]>0?0:1;--y;
  for(i=x-1;i>y;--i){
    if(j[i]<0){
      j[i]=-j[i];
      if(!f){j[i-1]-=1;j[i]=10-j[i];}
    }else if(j[i]>0&&f)j[i-1]+=1,j[i]=10-j[i];
    j[i]+=0x30;
  }
  if(j[0]==0x30)++y;
  if(++y){ x-=y;y=0;while(y<x)j[y]=j[y+1],++y;j[y]=0; }
  if(j[0]==0)j[0]=0x30,f=0;
  if(f){ for(i=x-1+f;i>0;--i)j[i]=j[i-1];j[0]=0x2d; }
  return j;
}
int main(){
  char m[998],n[998];scanf("%s %s",&m,&n);
  char*r=bigSub(m,n);printf("%s",r);free(r);
  return 0;
}