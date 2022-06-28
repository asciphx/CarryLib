#include <type_traits>
#include <string>
#include <string_view>
#include <stdexcept>
namespace std {
  template <typename T> inline T lexical_cast(const char* c);
  template <typename T> inline typename std::enable_if<std::is_fundamental<T>::value, std::string>::type lexical_cast(T&& t);
  template <typename S, typename T>
  inline typename std::enable_if<std::is_fundamental<std::decay_t<T>>::value&&
	std::is_same<S, std::string>::value, std::string>::type lexical_cast(T&& t);
  template <typename S> inline S lexical_cast(std::string_view t);
  template <> inline std::string lexical_cast<std::string>(const char* c);
  template <> [[nodiscard]] inline bool lexical_cast<bool>(const char* c);
  template <> [[nodiscard]] inline signed char lexical_cast<signed char>(const char* c);
  template <> [[nodiscard]] inline unsigned char lexical_cast<unsigned char>(const char* c);
  template <> [[nodiscard]] inline short lexical_cast<short>(const char* c);
  template <> [[nodiscard]] inline unsigned short lexical_cast<unsigned short>(const char* c);
  template <> [[nodiscard]] inline int lexical_cast<int>(const char* c);
  template <> [[nodiscard]] inline unsigned int lexical_cast<unsigned int>(const char* c);
  template <> [[nodiscard]] inline long long lexical_cast<long long>(const char* c);
  template <> [[nodiscard]] inline unsigned long long lexical_cast<unsigned long long>(const char* c);
  template <> [[nodiscard]] inline float lexical_cast<float>(const char* c);
  template <> [[nodiscard]] inline double lexical_cast<double>(const char* c);
  template <> [[nodiscard]] inline long double lexical_cast<long double>(const char* c);
  template <> inline tm lexical_cast<tm>(const char* c);
  template <typename T>
  T lexical_cast(const char* c) {
	static_assert(std::is_convertible<std::string, T>::value,
	  "Impossible to convert T from std::string. Please make your own lexical_cast() function");
	throw std::invalid_argument("");
  }
  template <typename T>
  typename std::enable_if<std::is_fundamental<T>::value, std::string>::type lexical_cast(T&& t) {
	return std::to_string(std::forward<T>(t));
  };
  template <typename S, typename T>
  typename std::enable_if<std::is_fundamental<std::decay_t<T>>::value&&
	std::is_same<S, std::string>::value, std::string>::type lexical_cast(T&& t) {
	return std::to_string(std::forward<T>(t));
  }
  template <typename S>
  S lexical_cast(std::string_view t) {
	return std::lexical_cast<S>(t.data());
  }
  template <>
  std::string lexical_cast<std::string>(const char* c) {
	return std::string(c);
  }
  template <>
  bool lexical_cast<bool>(const char* c) {
	if ((c[0] == 't' && c[1] == 'r' && c[2] == 'u' && c[3] == 'e' && c[4] == 0) ||
	(c[0] == '1' && c[1] == 0)) return true;
	if ((c[0] == 'f' && c[1] == 'a' && c[2] == 'l' && c[3] == 's' && c[4] == 'e' && c[5] == 0) ||
	(c[0] == '0' && c[1] == 0)) return false; throw std::invalid_argument("");
  }
  template <>
  signed char lexical_cast<signed char>(const char* c) {
	signed char r; if (*c == '-') {
	  r = 0x30 - *++c; if (*c > 0x39 || 0x30 > *c) throw std::runtime_error("");
	  while (*++c) {
		r = r * 10 - *c + 0x30; if (r >= 0 || *c > 0x39 || 0x30 > *c) throw std::runtime_error("");
	  };
	} else {
	  if (*c > 0x39 || 0x30 > *c) throw std::runtime_error(""); r = *c - 0x30;
	  while (*++c) {
		r = r * 10 + *c - 0x30; if (r <= 0 || *c > 0x39 || 0x30 > *c) throw std::runtime_error("");
	  }
	} return r;
  }
  template <>
  unsigned char lexical_cast<unsigned char>(const char* c) {
	if (*c > 0x39 || 0x30 > *c) throw std::runtime_error(""); unsigned char r = *c - 0x30; char z = 0;
	while (z != 1 && *++c) {
	  if (*c > 0x39 || 0x30 > *c) throw std::runtime_error(""); r = r * 10 + *c - 0x30; ++z;
	}
	if (z == 1 && *++c) {
	  if (r > 25 || *c > 0x39 || 0x30 > *c) throw std::runtime_error("");
	  r = r * 10 + *c - 0x30;
	  if (10 > r) throw std::runtime_error("");
	} return r;
  }
  template <>
  short lexical_cast<short>(const char* c) {
	short r; if (*c == '-') {
	  r = 0x30 - *++c; if (*c > 0x39 || 0x30 > *c) throw std::runtime_error("");
	  while (*++c) {
		r = r * 10 - *c + 0x30; if (r >= 0 || *c > 0x39 || 0x30 > *c) throw std::runtime_error("");
	  };
	} else {
	  if (*c > 0x39 || 0x30 > *c) throw std::runtime_error(""); r = *c - 0x30;
	  while (*++c) {
		r = r * 10 + *c - 0x30; if (r <= 0 || *c > 0x39 || 0x30 > *c) throw std::runtime_error("");
	  }
	} return r;
  }
  template <>
  unsigned short lexical_cast<unsigned short>(const char* c) {
	if (*c > 0x39 || 0x30 > *c) throw std::runtime_error(""); unsigned short r = *c - 0x30; char z = 0;
	while (z != 3 && *++c) {
	  if (*c > 0x39 || 0x30 > *c) throw std::runtime_error(""); r = r * 10 + *c - 0x30; ++z;
	}
	if (z == 3 && *++c) {
	  if (r > 6553 || *c > 0x39 || 0x30 > *c) throw std::runtime_error("");
	  r = r * 10 + *c - 0x30;
	  if (10 > r) throw std::runtime_error("");
	} return r;
  }
  template <>
  int lexical_cast<int>(const char* c) {
	int r; if (*c == '-') {
	  r = 0x30 - *++c; if (*c > 0x39 || 0x30 > *c) throw std::runtime_error("");
	  while (*++c) {
		r = r * 10 - *c + 0x30; if (r >= 0 || *c > 0x39 || 0x30 > *c) throw std::runtime_error("");
	  };
	} else {
	  if (*c > 0x39 || 0x30 > *c) throw std::runtime_error(""); r = *c - 0x30;
	  while (*++c) {
		r = r * 10 + *c - 0x30; if (r <= 0 || *c > 0x39 || 0x30 > *c) throw std::runtime_error("");
	  }
	} return r;
  }
  template <>
  unsigned int lexical_cast<unsigned int>(const char* c) {
	if (*c > 0x39 || 0x30 > *c) throw std::runtime_error(""); unsigned int r = *c - 0x30; char z = 0;
	while (z != 8 && *++c) {
	  if (*c > 0x39 || 0x30 > *c) throw std::runtime_error(""); r = r * 10 + *c - 0x30; ++z;
	}
	if (z == 8 && *++c) {
	  if (r > 429496729 || *c > 0x39 || 0x30 > *c) throw std::runtime_error("");
	  r = r * 10 + *c - 0x30;
	  if (10 > r) throw std::runtime_error("");
	} return r;
  }
  template <>
  long long lexical_cast<long long>(const char* c) {
	long long r; if (*c == '-') {
	  r = 0x30 - *++c; if (*c > 0x39 || 0x30 > *c) throw std::runtime_error("");
	  while (*++c) {
		r = r * 10 - *c + 0x30; if (r >= 0 || *c > 0x39 || 0x30 > *c) throw std::runtime_error("");
	  };
	} else {
	  if (*c > 0x39 || 0x30 > *c) throw std::runtime_error(""); r = *c - 0x30;
	  while (*++c) {
		r = r * 10 + *c - 0x30; if (r <= 0 || *c > 0x39 || 0x30 > *c) throw std::runtime_error("");
	  }
	} return r;
  }
  template <>
  unsigned long long lexical_cast<unsigned long long>(const char* c) {
	if (*c > 0x39 || 0x30 > *c) throw std::runtime_error(""); unsigned int r = *c - 0x30; char z = 0;
	while (z != 18 && *++c) {
	  if (*c > 0x39 || 0x30 > *c) throw std::runtime_error(""); r = r * 10 + *c - 0x30; ++z;
	}
	if (z == 18 && *++c) {
	  if (r > 1844674407370955161 || *c > 0x39 || 0x30 > *c) throw std::runtime_error("");
	  r = r * 10 + *c - 0x30;
	  if (10 > r) throw std::runtime_error("");
	} return r;
  }
  template <>
  float lexical_cast<float>(const char* _Ptr) {
	char* _Eptr; float _Ans = ::strtof(_Ptr, &_Eptr);
	if (_Ptr == _Eptr) { throw std::runtime_error(""); } return _Ans;
  }
  template <>
  double lexical_cast<double>(const char* _Ptr) {
	char* _Eptr; const double _Ans = ::strtod(_Ptr, &_Eptr);
	if (_Ptr == _Eptr) { throw std::runtime_error(""); } return _Ans;
  }
  template <>
  long double lexical_cast<long double>(const char* _Ptr) {
	char* _Eptr; const long double _Ans = ::strtold(_Ptr, &_Eptr);
	if (_Ptr == _Eptr) { throw std::runtime_error(""); } return _Ans;
  }
  template <>
  tm lexical_cast<tm>(const char* c) {
	int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0; tm t;
	if (sscanf(c, "%4d-%2d-%2d %2d:%2d:%2d", &year, &month, &day, &hour, &min, &sec) == 6) {
	  t.tm_mday = day;
	  t.tm_hour = hour;
	  t.tm_min = min;
	  t.tm_sec = sec;
	}
	t.tm_year = year - 1900;
	t.tm_mon = month - 1;
	return t;
  }
}
#include <iostream>
int main() {
  printf("%.6lf\n", std::lexical_cast<double>("54345.5466"));
  std::cout << std::lexical_cast<float>("255.496233") << '\n';
  std::cout << std::lexical_cast<unsigned int>("4294967295") << '\n';
  std::cout << std::lexical_cast<unsigned long long>("18446744073709551615") << '\n';
  return 0;
}