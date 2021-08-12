#include <iostream>
#include <type_traits>
#include <vector>
using namespace std;
template<typename T> char* getObjectName() {
  const char* s = typeid(T).name(); int i = 1;
  while (*++s); while (*--s != 0x20)++i;
  char* c = (char*)malloc(sizeof(char) * i);
  i = 0; while (*++s)c[i++] = *s; c[i] = 0; return c;
}
template <class N> constexpr const N& __(N*) {}
#define T_(N) { #N, typeid(__(&this->N)).name(), sizeof(&this->N) }
struct _proto_ { const char* name; const char* type; uint16_t size; };
typedef vector<_proto_> _;//serialization
template <class N, class T> _proto_ getConstructor(T& a, uint16_t i) {
  if (i >= a.$.size())i = a.$.size() - 1; return a.$[i];
}
template <class N, class T>constexpr N& getIdex(T& a, uint16_t i) {
  if (i >= a.$.size())i = a.$.size() - 1; uint16_t r = 0;
  for (uint8_t l = 0; l < i; ++l) r += a.$[l].size;
  return *reinterpret_cast<N*>(reinterpret_cast<char*>(&a) + r);
}
struct S {
  S() {} S(float a, int b, char* c) : a(a), b(b), c(c) { }
  float a;
  int b;
  char* c;

  _ ${ T_(a), T_(b), T_(c) };
};
struct Employee {
  string name;//basic_string
  double id;
  float age;
  S s;

  _ ${ T_(name),T_(id),T_(age),T_(s) };
};
int main() {
  char* sss = std::move(getObjectName<Employee>());
  S s{ 1.4f, 2, "hello" };
  cout << sss << endl;
  Employee ee; for (auto& m : ee.$)cout << m.name << " " << m.type << endl;
  _proto_ c = getConstructor<S>(s, 2);
  cout << c.type << " || " << endl;
  cout << getIdex<float>(s, 0) << endl;
  cout << getIdex<int>(s, 1) << endl;
  cout << getIdex<char*>(s, 2) << endl << endl;
  return 0;
}