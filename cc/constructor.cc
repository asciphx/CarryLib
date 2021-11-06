#include <typeinfo>
#include <iostream>
#include <vector>
using namespace std;
struct _proto_ { const char* name; const char* type; size_t offset; };
typedef vector<_proto_> __;//serialization
#define F_(T, N) { #N, typeid(N).name(),(size_t)(&reinterpret_cast<char const volatile&>(((T*)0)->N))  }
template <class N, class T> _proto_ getConstructor(T& a, size_t i) {
  if (i >= a.$.size())i = a.$.size() - 1; return a.$[i];
}
template <class N, class T> N& getIdex(T& a, size_t i) {
  if (i >= a.$.size())i = a.$.size() - 1;
  return *reinterpret_cast<N*>(reinterpret_cast<char*>(&a) + a.$[i].offset);
}
struct S {
  using _ = S;
  float a;
  string b;
  char* c;
  int d;
  S(float a, string b, char* c, int d) : a(a), b(b), c(c), d(d) {}
  __ ${ F_(_, a),F_(_, b) ,F_(_, c) ,F_(_, d) };
};
int main() {
  S s{ 1.3f, "world", "hello", 8 };
  for (auto& m : s.$)
    cout << m.name << " " << m.type << " " << m.offset << endl;
  cout << endl << getIdex<float>(s, 0) << endl;
  cout << getIdex<string>(s, 1) << endl;
  cout << getIdex<char*>(s, 2) << endl;
  _proto_ c = getConstructor<S>(s, 0);
  cout << c.name << endl;
  getIdex<float>(s, 0) = 3.0f;
  const type_info* nInfo = &typeid(S);
  cout << nInfo->name() << endl;
}
