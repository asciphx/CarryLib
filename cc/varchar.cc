#pragma once
#include <string.h>
#include <assert.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <iosfwd>
template<unsigned short I = 0x64>//Max [65534(char),16383(utf8)], Min 1, default 100.
class varchar {//It is similar to a dynamic std::string_view with a fixed maximum length
  unsigned short k = 0, l = 0, u = 0; char* _ = new char[I * 4 + 3];
  constexpr const static unsigned short ___ = I * 4 + 3;
  template<unsigned short A, unsigned short K> friend varchar<A> operator+(varchar<A>& t, const varchar<K>& $);
  template<unsigned short B> friend varchar<B> operator+(const char* c, varchar<B>& t);
  template<unsigned short C> friend varchar<C> operator+(const char c, varchar<C>& t);
  template<unsigned short D> friend varchar<D> operator+(varchar<D>& t, const char* c);
  template<unsigned short E> friend varchar<E> operator+(varchar<E>& t, const std::string& $);
  friend std::string& operator<<(std::string& s, varchar<I>& c) {
	s.push_back('"'); s += c.c_str(); s.push_back('"'); return s;
  };
  friend std::string& operator<<(std::string& s, const varchar<I>& c) {
	s.push_back('"'); s += c.c_str(); s.push_back('"'); return s;
  };
  friend std::ostream& operator<<(std::ostream& s, varchar<I>& c) { return s << c.c_str(); };
  constexpr const static unsigned char UTF$[256] =
  { 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 2, 2 };
public:
  ~varchar() { delete[]_; _ = nullptr; };
  varchar() { static_assert(I != 0 && I < 0x4000); _[0] = 0; };
  varchar(const char* s) {
	static_assert(I != 0 && I < 0x4000); while (*s && k < I) {
	  u = UTF$[static_cast<unsigned char>(*s)]; while (--u) _[l] = *s++, ++l; ++k;
	} _[l] = 0;
  };
  varchar(const varchar& str) { strcpy(_, str._); l = str.l; k = str.k; }
  template<unsigned short L> varchar(varchar<L>& s) { static_assert(I >= L); strcpy(_, s.c_str()); l = s.length(); k = s.u8size(); }
  varchar(const std::string& s) {
	while (s[l] && k < I) { u = UTF$[static_cast<unsigned char>(s[l])]; while (--u) { _[l] = s[l]; ++l; } ++k; } _[l] = 0;
  }
  varchar& operator = (const char* s) {
	delete[]_; _ = new char[___]; l = k = 0;
	while (s[l] && k < I) { u = UTF$[static_cast<unsigned char>(s[l])]; while (--u) { _[l] = s[l]; ++l; } ++k; } _[l] = 0;
	return *this;
  }
  varchar& operator = (const std::string& s) {
	delete[]_; _ = new char[___]; l = k = 0;
	while (s[l] && k < I) { u = UTF$[static_cast<unsigned char>(s[l])]; while (--u) { _[l] = s[l]; ++l; } ++k; } _[l] = 0;
	return *this;
  }
  varchar& operator = (const varchar& s) { delete[]_; _ = new char[___]; strcpy(_, s._); l = s.l; k = s.k; return *this; }
  template<unsigned short L>
  varchar& operator = (const varchar<L>& s) {
	delete[]_; _ = new char[___]; strncpy(_, s.c_str(), I * 4 + 2); l = s.length(); k = s.u8size(); _[l] = 0; return *this;
  }
  inline const char* c_str() const { return _; }//Same as std::string
  inline const unsigned short length() const { return l; }//Same as std::string
  inline const unsigned short u8size() const { return k; }//utf8Size
  inline char& operator()(unsigned short i) { return i < l ? _[i] : _[l]; }//Same as std::string
  inline varchar<1> operator[](unsigned short i) {
	varchar<1> txt; if (i > k)return txt; unsigned short h = 0, g = 0;
	const unsigned char* f = reinterpret_cast<unsigned char*>(_);
	while (h < i) u = UTF$[*f] - 1, ++h, f += u; u = UTF$[*f];
	while (++g < u) { txt += *f++; } txt += (char)0; return txt;
  }
  inline void operator +=(const char* c) {
	while (*c && k < I) { u = UTF$[static_cast<unsigned char>(*c)]; while (--u) { _[l++] = *c++; } ++k; } _[l] = 0;
  }//Safe, like std::string
  inline void operator +=(char c) { _[l++] = c; ++k; }//Incomplete safety, but it's generally safe and fast(maybe need .end())
  inline void operator <<(char c) { _[l++] = c; _[l] = 0; ++k; }//Safety
  void operator += (const varchar& t) {
	const char* s = t.c_str();
	if (&t == this) {
	  int i = 2 * k, p = 0; if (i > I)i = I; while (k < i) {
		u = UTF$[static_cast<unsigned char>(s[p])]; while (--u) { _[l++] = s[p++]; } ++k;
	  } _[l] = 0;
	} else {
	  unsigned short i = 0; while (s[i] && k < I) {
		u = UTF$[static_cast<unsigned char>(s[i])]; while (--u) { _[l++] = s[i++]; } ++k;
	  } _[l] = 0;
	}
  }
  template<unsigned short L>
  void operator += (const varchar<L>& t) {
	const char* s = t.c_str(); while (*s && k < I) {
	  u = UTF$[static_cast<unsigned char>(*s)]; while (--u) { _[l++] = *s++; } ++k;
	} _[l] = 0;
  }
  void operator += (const std::string& t) {
	const char* s = t.c_str(); while (*s && k < I) {
	  u = UTF$[static_cast<unsigned char>(*s)]; while (--u) { _[l++] = *s++; } ++k;
	} _[l] = 0;
  }
  inline void push_back(const char c) { if (k < I) _[l++] = c, ++k; }
  inline void push_begin(const char c) { unsigned short i = l; while (i) { _[i] = _[i - 1]; --i; } _[++l] = 0; _[0] = c, ++k; }
  inline void end() { _[l] = 0; }
  inline void clear() { _[0] = l = k = 0; }
};
template<unsigned short I>
std::ostream& operator<<(std::ostream& s, varchar<I> c) { return s << c.c_str(); }
template<unsigned short I>
varchar<I> operator+(varchar<I>& t, const char* c) {
  unsigned short& l = *((unsigned short*)(&t)), & k = *((unsigned short*)(reinterpret_cast<char*>(&t)
	+ (char)(&reinterpret_cast<char const volatile&>(((varchar<I>*)0)->*&varchar<I>::l)))); while (*c && l < I) {
	unsigned char u = varchar<I>::UTF$[static_cast<unsigned char>(*c)];
	while (--u) t(k) = *c++, ++k; ++l;
  } t(k) = 0; return t;
}
template<unsigned short I>
varchar<I> operator+(varchar<I>& t, const std::string& $) {
  unsigned short& l = *((unsigned short*)(&t)), & k = *((unsigned short*)(reinterpret_cast<char*>(&t)
	+ (char)(&reinterpret_cast<char const volatile&>(((varchar<I>*)0)->*&varchar<I>::l))));
  char* c = (char*)$.c_str(); while (*c && l < I) {
	unsigned char u = varchar<I>::UTF$[static_cast<unsigned char>(*c)];
	while (--u) t(k) = *c++, ++k; ++l;
  } t(k) = 0; return t;
}
template<unsigned short I, unsigned short K>
varchar<I> operator+(varchar<I>& t, const varchar<K>& $) {
  unsigned short& l = *((unsigned short*)(&t)), & k = *((unsigned short*)(reinterpret_cast<char*>(&t)
	+ (char)(&reinterpret_cast<char const volatile&>(((varchar<I>*)0)->*&varchar<I>::l))));
  char* c = (char*)$.c_str(); while (*c && l < I) {
	unsigned char u = varchar<I>::UTF$[static_cast<unsigned char>(*c)];
	while (--u) t(k) = *c++, ++k; ++l;
  } t(k) = 0; return t;
}
template<unsigned short I>
std::string operator+(std::string& t, const varchar<I>& $) {
  char* c = (char*)$.c_str(); while (*c) { t.push_back(*c); ++c; } t.push_back(0); return t;
}
template<unsigned short I>
varchar<I> operator+(const char* c, varchar<I>& t) {
  varchar<I> f; unsigned short& l = *((unsigned short*)(&f)), & k = *((unsigned short*)(reinterpret_cast<char*>(&f)
	+ (char)(&reinterpret_cast<char const volatile&>(((varchar<I>*)0)->*&varchar<I>::l))));
  while (*c && l < I) { unsigned char u = varchar<I>::UTF$[static_cast<unsigned char>(*c)];while (--u)f(k) = *c++, ++k; ++l; }
  f += t; return f;
}
template<unsigned short I>
varchar<I> operator+(const char c, varchar<I>& t) {
  unsigned short& l = *((unsigned short*)(&t)), & k = *((unsigned short*)(reinterpret_cast<char*>(&t)
	+ (char)(&reinterpret_cast<char const volatile&>(((varchar<I>*)0)->*&varchar<I>::l)))), i = k;
	while (i) { t(i) = t(i - 1); --i; } ++l; t(0) = c; t(++k) = 0; return t;
}
template<class T>
struct is_varchar: std::false_type {};
template<class T>
struct is_varchar<T[]>: std::false_type {};
template<unsigned short N>
struct is_varchar<varchar<N>>: std::true_type {};
inline const char* varcharify(const char* t) { return t; }
inline const char* varcharify(const std::string& t) { return t.c_str(); }
inline const std::string varcharify(const tm& _v) {
  std::ostringstream os; os << std::setfill('0');
#ifdef _WIN32
  os << std::setw(4) << _v.tm_year + 1900;
#else
  int y = _v.tm_year / 100; os << std::setw(2) << 19 + y << std::setw(2) << _v.tm_year - y * 100;
#endif
  os << '-' << std::setw(2) << (_v.tm_mon + 1) << '-' << std::setw(2) << _v.tm_mday << ' ' << std::setw(2)
	<< _v.tm_hour << ':' << std::setw(2) << _v.tm_min << ':' << std::setw(2) << _v.tm_sec; return os.str();
}
template<unsigned short I>
inline const char* varcharify(const varchar<I>& t) { return t.c_str(); }
template<typename T>
inline typename std::enable_if<std::is_fundamental<T>::value, const std::string>::type varcharify(const T& t) { return std::to_string(t); }
template<unsigned short I, typename T>
varchar<I * 2> operator!=(const varchar<I>& o, const T& v) {
  varchar<I * 2> x(o); x += '<'; x += '>';
  if constexpr (std::is_same<T, std::string>::value || std::is_same<T, tm>::value || std::is_same<T, const char*>::value) {
	x += '\''; x += varcharify(v); x += '\'';
  } else {
	x += varcharify(v);
  } x += (char)0; return x;
}
template<unsigned short I, typename T>
varchar<I * 2> operator==(const varchar<I>& o, const T& v) {
  varchar<I * 2> x(o); x += '=';
  if constexpr (std::is_same<T, std::string>::value || std::is_same<T, tm>::value || std::is_same<T, const char*>::value) {
	x += '\''; x += varcharify(v); x += '\'';
  } else {
	x += varcharify(v);
  } x += (char)0; return x;
}
template<unsigned short I, typename T>
varchar<I * 2> operator<(const varchar<I>& o, const T& v) {
  varchar<I * 2> x(o); x += '<';
  if constexpr (std::is_same<T, std::string>::value || std::is_same<T, tm>::value || std::is_same<T, const char*>::value) {
	x += '\''; x += varcharify(v); x += '\'';
  } else {
	x += varcharify(v);
  } x += (char)0; return x;
}
template<unsigned short I, typename T>
varchar<I * 2> operator<=(const varchar<I>& o, const T& v) {
  varchar<I * 2> x(o); x += '<'; x += '=';
  if constexpr (std::is_same<T, std::string>::value || std::is_same<T, tm>::value || std::is_same<T, const char*>::value) {
	x += '\''; x += varcharify(v); x += '\'';
  } else {
	x += varcharify(v);
  } x += (char)0; return x;
}
template<unsigned short I, typename T>
varchar<I * 2> operator>=(const varchar<I>& o, const T& v) {
  varchar<I * 2> x(o); x += '>'; x += '=';
  if constexpr (std::is_same<T, std::string>::value || std::is_same<T, tm>::value || std::is_same<T, const char*>::value) {
	x += '\''; x += varcharify(v); x += '\'';
  } else {
	x += varcharify(v);
  } x += (char)0; return x;
}
template<unsigned short I, typename T>
varchar<I * 2> operator>(const varchar<I>& o, const T& v) {
  varchar<I * 2> x(o); x += '>';
  if constexpr (std::is_same<T, std::string>::value || std::is_same<T, tm>::value || std::is_same<T, const char*>::value) {
	x += '\''; x += varcharify(v); x += '\'';
  } else {
	x += varcharify(v);
  } x += (char)0; return x;
}
template<unsigned short I, unsigned short L>
varchar<I + L + 7> operator&&(varchar<I> o, const varchar<L>& c) {
  varchar<I + L + 7> x; x += '('; x += o; x += " AND "; x += c; x += ')'; x.end(); return x;
};
template<unsigned short I, unsigned short L>
varchar<I + L + 6> operator||(varchar<I> o, const varchar<L>& c) {
  varchar<I + L + 6> x; x += '('; x += o; x += " OR "; x += c; x += ')'; x.end(); return x;
};
template<unsigned short I, typename T>
std::string operator>>(varchar<I> o, const std::vector<T>& c) {
  std::string s(o.c_str()); s += " IN("; size_t l = c.size(); if (l > 0) {
	s += varcharify(c[0]); for (size_t i = 1; i < l; ++i) { s += ',', s += varcharify(c[i]); }
  } s.push_back(')'); return s;
};

int main() {
#ifdef _WIN32
  system("chcp 65001 >nul");
#endif
  varchar<16> f = "wtf!", k = "wwzzgg"; std::string s = "sdg";
  varchar<256> d = "sd"; varchar<6> u = "wtf!"; varchar<4> y = "wtf!"; u = u + y; std::cout << u << u.length();
  d = 'y' + d; d.push_begin('$'); std::cout << d << d.length() << '\n'; d = "fghfg" + d;
  std::cout << (d && d) << d.length() << '\n';
  varchar<19> z = "你好!"; z += z + "#"; z += s;
  std::cout << z << z.length() << '\n';
  d = ("ggg" + f || k); d.push_begin('$'); std::cout << d << d.length();
  return 0;
}
