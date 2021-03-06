#pragma once
#include <cstdlib>
#ifdef __cplusplus
extern "C" {
#endif
  static char RES_ASCII[97] = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
  int strLen(const char* s) { const char* e = s; while (*++e); return e - s; }
  void strCpy(char* d, const char* s) { while (*s) { *d++ = *s++; }*d = 0; }
  char* strStr(char* d, const char* s) {
    int i = 0, j = 0, l = strLen(d), k = strLen(s);
    while (i < l&& j < k) if (d[i] == s[j])i++, j++; else i = i - j + 1, j = 0;
    if (j == k) return d + i - k; return (char*)0;
  }
  int strCmp(const char* c, const char* s) {
    if (c[0] == 0 || s[0] == 0)return -1; while (*s == *c && *c && *s)c++, s++;
    if (*c == *s)return 0; if (*c > *s)return 1; return -1;
  }
  int find1CharPosDESC(const char* c, const char d) {
    for (int l = strLen(c), i = l - 1; i > 0; --i)if (c[i] == d)return l - i; return -1;
  }
  int find1CharPosASC(const char* c, const char d) {
    for (int l = strLen(c), i = 0; i < l; ++i)if (c[i] == d)return i; return -1;
  }
  //other not safe
  char* subStr(const char* c, int i, int e) {
    if (e < i || i < 0)return (char*)0;
    char* w = (char*)malloc(sizeof(char) * (e - i + 1)); int p = 0; while (i < e)w[p++] = c[i++]; w[p] = 0; return w;
  }
  char* joinS2CInInt(const char* c, int i, const char* s) {
    int j = strLen(s), l = strLen(c), p = 0, n = 0, m = 0;
    char* w = (char*)malloc(sizeof(char) * (l + j));
    --i; while (p < i)w[p++] = c[n++]; while (m < j)w[p++] = s[m++];
    while (n < l)w[p++] = c[n++]; w[p] = '\0'; return w;
  }
  char* toStrL(unsigned long long i) {
    int z = 2; for (unsigned long long a = i; a > 0x7f; a -= 0x7f, a /= 0x100, ++z);
    unsigned long long b, t = i / 0x100; b = i - t * 0x100 - 32;
    char* w = (char*)malloc(sizeof(char) * z); w[--z] = '\0';
    while (t > 0x7f) {
      w[--z] = RES_ASCII[b]; i = t; t = i / 0x100; b = i - t * 0x100 - 32;
    }
    w[--z] = RES_ASCII[b]; if (z > 0) { t -= 32; w[0] = RES_ASCII[t]; }
    return w;
  }
  char* toStr(int i) {
    int t = i / 0x100, b = i - t * 0x100 - 32, z = i > 0x7f7f7f ? 5 : i > 0x7f7f ? 4 : i > 0x7f ? 3 : 2;
    char* w = (char*)malloc(sizeof(char) * (z)); w[--z] = '\0';
    while (t > 0x7f) { w[--z] = RES_ASCII[b]; i = t; t = i / 0x100; b = i - t * 0x100 - 32; }
    w[--z] = RES_ASCII[b]; if (z > 0) { t -= 32; w[0] = RES_ASCII[t]; } return w;
  }
  constexpr unsigned long long hack8Str(const char* s) {
    unsigned long long r = 0; for (int i = 0; s[i]; r *= 0x100, r += s[i++]); return r;
  }
  constexpr int hack4Str(const char* s) { int r = 0; for (int i = 0; s[i]; r *= 0x100, r += s[i++]); return r; }
  int hack_str(const char* oid) {
    int t = 0, i = strLen(oid), j, pow = 1;
    while (i-- > 0) {
      char* chr = subStr(oid, i, i + 1); j = 0;
      while (j++ < 0x61) {
        char* s = subStr(RES_ASCII, j - 1, j);
        if (strCmp(chr, s) == 0) {
          t = t + (j + 0x1f) * pow; pow = pow * 0x100; free(s); break;
        } free(s);
      } free(chr);
    } return t;
  }

#ifdef __cplusplus
}  /* extern "C" */
#endif
