#include <string>
#include <iostream>
using namespace std;
template <typename T,int N>
class Array{private:T arr[N];
public:int Size()const{return N;}};
template <typename T> void print(T& x) { std::cout << x << std::endl; }
template <typename S, typename... Args>
void print(S s, Args... a) { std::cout << s; print<Args...>(a...); }

int main(){
  Array<int,5>arr;
  print(arr.Size());
  cin.get();
  print(1, " dsag ", 1.5f, " ", 3.14);
}