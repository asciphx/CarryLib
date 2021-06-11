#include <string>
#include <iostream>
using namespace std;
// template <typename... Args>
template <typename T>
void Print(T value){
  cout<<value<<endl;
}
template <typename T,int N>
class Array{private:T arr[N];
public:int Size()const{return N;}};
int main(){
  Print<int>(55);Print(5.5f);
  Print<string>("dsgs");
  Array<int,5>arr;
  Print(arr.Size());
  cin.get();
}