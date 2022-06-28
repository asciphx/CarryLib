#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <sstream>
#define _TS(U) std::cout << typeid(U).name() << std::endl
int main() {
  _TS(double);
  _TS(tm);
  _TS(time_t);
  _TS(float);
  _TS(bool);
  _TS(std::string);
  _TS(int8_t);
  _TS(uint8_t);
  _TS(const char*);
  _TS(char*);
  _TS(char);
  _TS(short);
  _TS(unsigned short);
  _TS(int);
  _TS(unsigned int);
  _TS(long long);
  _TS(unsigned long long);
  return 0;
}