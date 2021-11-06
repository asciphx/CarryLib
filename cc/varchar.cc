#pragma once
#include <string.h>
#include <assert.h>
#include <iostream>
template<unsigned char I = 255>
struct varchar {
  ~varchar() { delete[]_; _ = nullptr; };
  varchar(const char* c_str = 0) {
	size_t i = strlen(c_str); if (i < I)l = i; strncpy(_, c_str, I); _[l] = 0;
  };
  varchar(const varchar& str) {
	strcpy(_, str._); l = str.l;
  }
  varchar(const std::string& str) {
	size_t i = str.length(); strncpy(_, str.c_str(), I); if (i < I)l = i; _[l] = 0;
  }
  varchar& operator = (const char* str) {
	delete[]_; _ = new char[I + 1]; strncpy(_, str, I); size_t n = strlen(str); l = I < n ? I : n; _[l] = 0; return *this;
  }
  varchar& operator = (const std::string& str) {
	delete[]_; _ = new char[I + 1]; strncpy(_, str.c_str(), I); size_t n = str.length(); l = I < n ? I : n; _[l] = 0; return *this;
  }
  varchar& operator = (const varchar& str) {
	delete[]_; _ = new char[I + 1]; strcpy(_, str._); l = str.l; return *this;
  }
  template<unsigned char L>
  varchar& operator = (const varchar<L>& str) {
	delete[]_; _ = new char[I + 1]; strncpy(_, str.c_str(), I); l = str.length(); _[l] = 0; return *this;
  }
  const char* c_str() const { return _; }
  const short length() const { return l; }
  char& operator[](unsigned char i) { return _[i]; }
  varchar& operator += (const char* c) {
	while (*c && l < I) { _[l++] = *c++; } _[I] = 0; return *this;
  }
  varchar& operator += (const varchar& t) {
	const char* s = t.c_str();
	if (&t == this) {
	  short i = 2 * l, k = -1; if (i > I)i = I; while (l < i) { _[l++] = s[++k]; } _[i] = 0;
	} else {
	  unsigned char i = 0xff; while (s[++i] && l < I) { _[l++] = s[i]; } _[I] = 0;
	}
	return *this;
  }
  template<unsigned char L>
  varchar& operator += (const varchar<L>& t) {
	const char* s = t.c_str(); unsigned char i = 0xff; while (s[++i] && l < I) { _[l++] = s[i]; } _[I] = 0; return *this;
  }
  varchar& operator += (const std::string& t) {
	unsigned char i = 0xff; while (t[++i] && l < I) { _[l++] = t[i]; } _[I] = 0; return *this;
  }
  varchar& push_back(const char c) {
	if (l < I) _[l++] = c; return *this;
  }
  varchar& pop_back() {
	_[--l] = 0; return *this;
  }
  friend std::string& operator<<(std::string& s, varchar<I>& c) {
	s.push_back('"'); s += c.c_str(); s.push_back('"'); return s;
  };
  friend std::ostream& operator<<(std::ostream& s, varchar<I>& c) {
	return s << c.c_str();
  };
private: char* _ = new char[I + 1]; unsigned char l = I;
};
template<unsigned char I>
varchar<I> operator+(const varchar<I>& t, const char* c) {
  unsigned char l = t.length(); char* s = (char*)t.c_str(); while (*c && l < I) { s[l++] = *c++; } s[l] = 0; return t;
}
template<class T>
struct is_varchar : std::false_type {};
template<class T>
struct is_varchar<T[]> : std::false_type {};
template<unsigned char N>
struct is_varchar<varchar<N>> : std::true_type {};

int main() {
  varchar<> f = "wtf!";
  varchar<16> z = "你好!"; z += z + "#";
  std::cout << z.c_str() << '\n';
  std::cout << f.c_str() << '\n' << "hahoa";
  return 0;
}