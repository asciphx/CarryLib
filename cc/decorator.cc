#include <iostream>
#define STR_1(k,i)  k[i]
#define STR_2(k,i)  k[i], STR_1(k,i+1)
#define STR_3(k,i)  k[i], STR_2(k,i+1)
#define STR_4(k,i)  k[i], STR_3(k,i+1)
#define STR_5(k,i)  k[i], STR_4(k,i+1)
#define STR_6(k,i)  k[i], STR_5(k,i+1)
#define STR_7(k,i)  k[i], STR_6(k,i+1)
#define STR_8(k,i)  k[i], STR_7(k,i+1)
#define STR_9(k,i)  k[i], STR_8(k,i+1)
#define STR_10(k,i) k[i], STR_9(k,i+1)
#define STR_11(k,i) k[i], STR_10(k,i+1)
#define STR_12(k,i) k[i], STR_11(k,i+1)
#define STR_13(k,i) k[i], STR_12(k,i+1)
#define STR_14(k,i) k[i], STR_13(k,i+1)
#define STR_15(k,i) k[i], STR_14(k,i+1)
#define STR_16(k,i) k[i], STR_15(k,i+1)
#define STR_17(k,i) k[i], STR_16(k,i+1)
#define STR_18(k,i) k[i], STR_17(k,i+1)
#define STR_19(k,i) k[i], STR_18(k,i+1)
#define STR_20(k,i) k[i], STR_19(k,i+1)
#define STR_21(k,i) k[i], STR_20(k,i+1)
#define STR_22(k,i) k[i], STR_21(k,i+1)
#define STR_23(k,i) k[i], STR_22(k,i+1)
#define STR_24(k,i) k[i], STR_23(k,i+1)
#define STR_25(k,i) k[i], STR_24(k,i+1)
#define STR_26(k,i) k[i], STR_25(k,i+1)
#define STR_27(k,i) k[i], STR_26(k,i+1)
#define STR_28(k,i) k[i], STR_27(k,i+1)
#define STR_29(k,i) k[i], STR_28(k,i+1)
#define STR_30(k,i) k[i], STR_29(k,i+1)
#define STR_31(k,i) k[i], STR_30(k,i+1)
#define STR_32(k,i) k[i], STR_31(k,i+1)
#define R(N) STR_32(N"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",0)
template<char... T>
struct router {
  char name[sizeof...(T) + 1] = { T..., 0 };
  void api(const char* c) {
	std::cout << name << c << '\n';
  };
  void printf() { std::cout << name << '\n'; };
};//支持32位长度的字符串模板装饰器
int main() {
  router<R("/api")> r;
  r.printf();//输出 /api
  r.api("/hello");//输出 /api/hello
  return 0;
}
