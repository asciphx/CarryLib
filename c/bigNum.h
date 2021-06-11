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
char*bigSub(const char*m,const char*n){
  if(m[0]==0||n[0]==0)return NULL;
  int i=0,l=0,x,y,f;char*j=(char*)calloc(999,sizeof(char));
  while(m[++i]);while(n[++l]);x=y=i>l?i:l;
  while(y--){if(i)j[y]+=m[--i]-0x30;if(l)j[y]-=n[--l]-0x30;}
  while(j[++y]==0);f=j[y]>0?0:1;--y;
  for(i=x-1;i>y;--i){
    if(j[i]<0){j[i]=-j[i];if(!f){j[i-1]-=1;j[i]=10-j[i];}
    }else if(j[i]>0&&f)j[i-1]+=1,j[i]=10-j[i];j[i]+=0x30;
  }
  if(j[0]==0x30)++y;
  if(++y) {x-=y;y=0;while(y<x)j[y]=j[y+1],++y;j[y]=0;}
  if(j[0]==0)j[0]=0x30,f=0;
  if(f){for(i=x-1+f;i>0;--i)j[i]=j[i-1];j[0]=0x2d;}
  return j;
}
char*bigMul(const char*m,const char*n){
  if(m[0]==0||n[0]==0)return NULL;
  int i=0,z=0,x,y,s;
  char*j=(char*)calloc(999,sizeof(char));
  for(x=0;m[x];++x)
    for(y=0;n[y];++y){
      j[x+y]+=(m[x]-0x30)*(n[y]-0x30);
      if(j[x+y]<0){
        s=j[x+y]+0x100;j[x+y-1]+=s/10;j[x+y]=s%10;
      }
    }
  for(i=z=x+y-1;i>0;){
    if(j[--i]<0){ s=j[i]+0x100;j[i-1]+=s/10;j[i]=s%10; }
    if(j[i]<10){ j[i]+=0x30;continue; }
    if(i>0)j[i-1]+=j[i]/10;else{y=0,x=j[i]/10;} 
    j[i]%=10;j[i]+=0x30;
  }
  if(!y){ j[z+1]=0;while(z--)j[z+1]=j[z];j[0]=x+0x30; }
  return j;
}
char*bigDiv(const char*m,const char*n){
  return NULL;
  
}