#include<stdio.h>
#include<stdlib.h>
char*bigMul(const char*m,const char*n){
  if(m[0]==0||n[0]==0)return NULL;
  int i=0,z=0,x,y,a,b,f,t;
  char*j=(char*)calloc(999,sizeof(char));
  a=m[0]=='-';b=n[0]=='-';f=a&&!b||!a&&b;
  for(x=a;m[x];++x)
    for(y=b;n[y];++y){
      t=x+y+f-z-b;
      j[t]+=(m[x]-0x30)*(n[y]-0x30);
      if(j[t]<0){
        j[t-1]+=(j[t]+0x100)/10;
        j[t]=(j[t]+0x100)%10;
      }
    }
  for(i=z=x+y-1+f;i>f;){
    if(j[--i]<0){ 
      t=j[i]+0x100;j[i-1]+=t/10;j[i]=t%10;
    }
    if(j[i]<10){ j[i]+=0x30;continue; }
    if(i>f)j[i-1]+=j[i]/10;else{y=0,x=j[i]/10;} 
    j[i]%=10;j[i]+=0x30;
  }
  if(f)j[0]=0x2d;
  if(!y){j[z+f+1]=0;while(z--)j[z+1+f]=j[z+f];j[f]=x+48;}
  return j;
}
int main(){
  char m[499],n[499];scanf("%s %s",m,n);
  char*j=bigMul(m,n);printf("[%s]",j);free(j);
  return 0;
}