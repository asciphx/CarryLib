#include <stdio.h>
#define toascii(c) (((unsigned char)(c))&0x7f)
static char ASCII[97]= " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
char*subStr(const char*c,int i,int e){if(e<i||i<0)return (char *)0;
  char*w=(char*)malloc(sizeof(char)*(e-i+1));int p=0;while(i<e)w[p++]=c[i++]; w[p]=0;return w;
}
int strCmp(const char *c,const char *s){
  if(c[0]==0||s[0]==0)return -1;while(*s==*c&&*c&&*s)c++,s++;
  if(*c==*s)return 0;if(*c>*s)return 1;else return -1;
}
void strCpy(char *d,const char *s){while(*s){*d++=*s++;}*d=0;}
int strLen(const char*s){const char*e=s;while(*++e);return e-s;}
int from_str(const char*oid){
  int this=0,i=strLen(oid),j,pow_256=1;
  while (i-->0){
    char*chr=subStr(oid,i,i+1);j=0;
    while (j++<97){
      char*s=subStr(ASCII,j-1,j);
      if(strCmp(chr,s)==0){
        this=this+(j+31)*pow_256; pow_256=pow_256*256;free(s);break;
      } free(s);
    } free(chr);
  } return this;
}
char*to_str(int i){
  int t=i/0x100,b=i-t*0x100-32,z=i>8355711?5:i>32639?4:i>127?3:2;
  char*w=(char*)malloc(sizeof(char)*(z));w[--z]='\0';
  while(t>127){ w[--z]=ASCII[b];i=t;t=i/0x100;b=i-t*0x100-32; }
  w[--z]=ASCII[b];if(z>0){t-=32;w[0]=ASCII[t];} return w;
}
int fromStr(const char*s){ int r=0;for(int i=0;s[i];r*=256,r+=s[i++]);return r; }
int main(void)
{
  char c[4][2]={"a","b","c","d"},cc[4]={'a','b','c','d'},ccc[5]="abcd";
  printf("%s  %s\n",to_str(from_str("~~~~")),to_str(fromStr("!!!!")));
  printf("Z ascii :%d 0:%c\n1:%d  2:%s  3:%s\n4:%c  5:%c\n",toascii('Z'),ASCII[1],c[0][0],c,c[3],cc[3],ccc[3]);
	return 0 ;
}