#include<iostream>
using namespace std;
template<typename T>
struct intint {
  T i;
  intint(T i) :i(i) {}
  operator T() { return i; }
};
template<int ...>struct seq {};
template<int N, int ...S> struct gen_seq : gen_seq<N - 1, N - 2, S...> {};
template<int ...S> struct gen_seq<1, S...> { typedef seq<S...> type; };
template<typename T, typename R, typename...TS>
struct callable {
  typename gen_seq<sizeof...(TS) + 1>::type fo;
  R(T::* func)(TS...);
  callable(R(T::* func)(TS...)) :func(func) {}
  template<int ...S>
  void call(seq<S...>, int* v) {
	(new T->*func)(intint(v[S])...);
  }
  void operator()(T*, int* v) {
	call(fo, v);
  }
};
struct foo {
  void func(int a, int b, int c, int d) {
	cout << a << b << c << d;
  }
};

int main()
{
  callable<foo, void, int, int, int, int> c(&foo::func);
  int v[] = { 100,200,300,400 };
  c(new foo(), v);
  return 0;
}