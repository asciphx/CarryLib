#include <stdarg.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#ifdef _WIN32
int isL=0x37;
#else
int isL=0x57;
#endif
int myPrintf(const char *frm, ...) {
  int cnt = 0, y, z;va_list arg;va_start(arg, frm);
  for (int i = 0;frm[i]; ++i)
    switch (frm[i]) {
      case '%': switch (frm[++i]) {
          case '%': putchar(frm[i]);++cnt;break;
          case 'o': { unsigned int t=va_arg(arg,unsigned int);y=0;
              char s[11];
              do{ 
                s[y++]=t%8+48;t/=8;++cnt;
              }while(t);
              while(y)putchar(s[--y]);
			  		} break;
          case 'x': { unsigned int t=va_arg(arg,unsigned int);y=0;
              char s[11];
              do{
                z=t%16;s[y++]=z>9?z+0x57:z+48;t/=16;++cnt;
              }while(t);
              while(y)putchar(s[--y]);
              } break;
          case 'p': { unsigned long t=va_arg(arg,unsigned long);y=0;putchar('0');
              if(isL==0x57)putchar('x');
              char s[11];
              do{
                z=t%16;s[y++]=z>9?z+isL:z+48;t/=16;++cnt;
              }while(t);if(y<7)s[y++]=48;
              while(y)putchar(s[--y]);
             } break;
          case 'c': { int t=va_arg(arg,int);putchar(t>128||t<-1?63:t); } break;
          case 'd':{
            int t = va_arg(arg,int);y=0;if(t<0)putchar('-'),++cnt;
            char s[11];
            do{ 
              s[y++]=t>0?t%10+48:-(t%10)+48;t/=10;++cnt;
            }while(t);
            while(y)putchar(s[--y]);
          } break;
          case 's':{
            const char*str=va_arg(arg,const char*);
            for (int i = 0;str[i]; i++){
              putchar(str[i]),++cnt;
            }
          } break;
          case 'l': switch (frm[++i]){
            case 'l':if(frm[++i]=='d'){
              long long t = va_arg(arg,long long);y=0;if(t<0)putchar('-'),++cnt;
              char s[19];
              do{ 
                s[y++]=t>0?t%10+48:-(t%10)+48;t/=10;++cnt;
              }while(t);
              while(y)putchar(s[--y]);
             }else continue;break;
             case 'd':{
              long t = va_arg(arg,long);y=0;if(t<0)putchar('-'),++cnt;
              char s[11];
              do{ 
                s[y++]=t>0?t%10+48:-(t%10)+48;t/=10;++cnt;
              }while(t);
              while(y)putchar(s[--y]);
             } break;
             case 'f':{
              double l=va_arg(arg,double);long long t=(long long)l;l-=t;
              y=z=0;if(t<0)putchar('-'),l=-l,++cnt;
              char s[26];
              do{ 
                s[y++]=t>0?t%10+48:-(t%10)+48;t/=10;++cnt;
              }while(t);
              while (y)putchar(s[--y]);s[y++]=0x2e;t=10;
              do{
                s[y++]=(int)((l+1e-6)*t)%10+48;t*=10;l-=(int)l;++cnt;
              }while(t<1000001);
              while (y>z)putchar(s[z++]);
             } break;
          } break;
        } break;
      default:putchar(frm[i]),++cnt;break;
    }va_end(arg);
  return cnt;
}
/** example
int main() { 
  myPrintf("INT32_MAX = %d\n",INT32_MAX);
  myPrintf("INT32_MIN = %d\n",INT32_MIN);
  myPrintf("INT32_MAX = %x\n",INT32_MAX);
  myPrintf("char = %c\n",-1);
  myPrintf("char = %lf\n",-801.235324);
  long long p=INT64_MAX;
  myPrintf("INT64_MAX = %p\n",&p);
  myPrintf("INT64_MAX = %lld\n",INT64_MAX);
  myPrintf("INT64_MIN = %lld\n",INT64_MIN);
  return 0;
}
*/