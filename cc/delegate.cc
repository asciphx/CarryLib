#include <iostream>
using namespace std;
template <class T, class R, typename... Args>
struct Delegate {
  Delegate(T* t, R(T::* f)(Args...)) :m_t(t), m_f(f) {}
  R operator()(Args&&... args) {
	return (m_t->*m_f)(std::forward<Args>(args) ...);
  }
private:
  T* m_t;
  R(T::* m_f)(Args...);
};
template <class T, class R, typename... Args>
Delegate<T, R, Args...> InitDelegate(T* t, R(T::* f)(Args...)) {
  return Delegate<T, R, Args...>(t, f);
}
struct A {
  void Fun(int i) { cout << i << endl; }
  void Fun1(int i, double j) { cout << i + j << endl; }
};
int main() {
  A a;
  auto d = InitDelegate(&a, &A::Fun); //初始化委托
  d(1); //调用委托
  auto d1 = InitDelegate(&a, &A::Fun1);
  d1(1, 2.5);
}