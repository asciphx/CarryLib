static char ASCII[97]= " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
//Do not need free(?);
int strLen(const char*s){const char*e=s;while(*++e);return e-s;}
void strCpy(char*d,const char*s){while(*s){*d++=*s++;}*d=0;}
char*strStr(char*d,const char*s) {
  int i=0,j=0,l=strLen(d),k=strLen(s);
	while(i<l&&j<k) if(d[i]==s[j])i++,j++;else i=i-j+1,j=0;
	if(j==k) return d+i-k; return (char *)0;
}
int strCmp(const char *c,const char *s){
  if(c[0]==0||s[0]==0)return -1;while(*s==*c&&*c&&*s)c++,s++;
  if(*c==*s)return 0;if(*c>*s)return 1;else return -1;
}
int find1CharPosDESC(const char*c,const char d){
  for(int l=strLen(c),i=l-1;i>0;--i)if(c[i]==d)return l-i;
}
int find1CharPosASC(const char*c,const char d){
  for(int l=strLen(c),i=0;i<l;++i)if(c[i]==d)return i;
}
//other
char*I2C(int d){
  char*j=(char*)calloc(11,sizeof(char));int i=0;
  while(d){j[i++]=d%10+0x30;d/=10;}j[i]=0;return j;
}
char*subStr(const char*c,int i,int e){if(e<i||i<0)return (char *)0;
  char*w=(char*)malloc(sizeof(char)*(e-i+1));int p=0;while(i<e)w[p++]=c[i++]; w[p]=0;return w;
}
char*joinS2CInInt(const char*c,int i,const char*s){
  int j=strLen(s),l=strLen(c),p=0,n=0,m=0;
  char*w=(char*)malloc(sizeof(char)*(l+j));
  --i;while(p<i)w[p++]=c[n++];while(m<j)w[p++]=s[m++];
  while(n<l)w[p++]=c[n++];w[p]='\0';return w;
}
char*toStrL(unsigned long long i){
  int z=2;for(unsigned long long a=i;a>127;a-=127,a/=256,++z);
  unsigned long long b,t=i/0x100;b=i-t*0x100-32;
  char*w=(char*)malloc(sizeof(char)*z);w[--z]='\0';
  while(t>127){
    w[--z]=ASCII[b];i=t;t=i/0x100;b=i-t*0x100-32;
  }
  w[--z]=ASCII[b];if(z>0){t-=32;w[0]=ASCII[t];}
  return w;
}
char*toStr(int i){
  int t=i/0x100,b=i-t*0x100-32,z=i>8355711?5:i>32639?4:i>127?3:2;
  char*w=(char*)malloc(sizeof(char)*(z));w[--z]='\0';
  while(t>127){ w[--z]=ASCII[b];i=t;t=i/0x100;b=i-t*0x100-32; }
  w[--z]=ASCII[b];if(z>0){t-=32;w[0]=ASCII[t];} return w;
}
unsigned long long fromStrL(const char*s){
  unsigned long long r=0;for(int i=0;s[i];r*=256,r+=s[i++]);return r;
}
int fromStr(const char*s){ int r=0;for(int i=0;s[i];r*=256,r+=s[i++]);return r; }
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