#include<iostream>
#include<string>
#include<vector>
#include<stdarg.h>
#define Size(arr) sizeof(arr)/sizeof(*arr)
using namespace std;
string formattedString(const char *f,...){
  string s(128,0); va_list vl,backup; va_start(vl,f); va_copy(backup,vl);
  auto r=vsnprintf((char *)s.data(),s.size(),f,backup);
  va_end(backup);
  if ((r>=0)&&((string::size_type)r<s.size()))
	s.resize(r);
  else while (true){
	if (r<0) s.resize(s.size()*2); else s.resize(r+1);
	va_copy(backup,vl);
	auto r=vsnprintf((char *)s.data(),s.size(),f,backup);
	va_end(backup);
	if ((r>=0)&&((string::size_type)r<s.size())){
	  s.resize(r);break;
	}
  }
  va_end(vl); return s;
}
enum class Sort{ ASC,DESC };
template<typename T>class Sql{
  public:
  Sql<T>(const string&client):client_(client+" "){ field("*"); }
  Sql<T>&limit(size_t limit);Sql<T>&offset(size_t offset);
  Sql<T>&orderBy(const string&col,const Sort&ord=Sort::ASC);
  Sql<T>&field(const string&str);
  Sql<T>&field(const string*arr,int l);
  Sql<T>&field(vector<string>&arr);
  string findAll()noexcept(false);
  private:
  string client_;size_t limit_{0},offset_{0};string orderBy_;string field_=" *";
  void clear(){ limit_=0;offset_=0;field_="*"; }
};
template<typename T>inline Sql<T>&Sql<T>::limit(size_t limit){ limit_=limit;return*this; }
template<typename T>inline Sql<T>&Sql<T>::offset(size_t offset){ offset_=offset;return*this; }
template<typename T>inline Sql<T>&Sql<T>::orderBy(const string&col,const Sort&ord){
  if (orderBy_.empty()){
	orderBy_=formattedString(" order by %s ",col.c_str());if (ord==Sort::DESC)orderBy_+="desc";
  } else{ orderBy_+=",";orderBy_+=col;if (ord==Sort::DESC)orderBy_+=" desc"; }return*this;
}
template<typename T>inline Sql<T>&Sql<T>::field(const string&str){ field_=str;return*this; }
template<typename T>inline Sql<T>&Sql<T>::field(vector<string>&arr){
  field_="";unsigned int l=arr.size();for (unsigned int i=0;i<l;++i){ if (i==l-1)field_+=arr[i];else field_+=arr[i]+","; }return *this;
}
template<typename T>inline Sql<T>&Sql<T>::field(const string*arr,int l){field_="";
  for (unsigned int i=0;i<l;++i){ if (i==l-1)field_+=arr[i];else field_+=arr[i]+","; }return *this;
}
template<typename T> const char* getObjectName() {
  const char* s = typeid(T).name();
#if _WIN32
  while (*++s != 0x20); return ++s;
#else
  while (*s < 0x3a && *s++ != 0x24) {}; return s;
#endif
}
template<typename T>inline string Sql<T>::findAll()noexcept(false){
  string sql=client_+field_+" from ";
  char*name=getObjectName<T>();
  sql+=name;free(name);sql+=orderBy_;
  if (offset_>0){ sql+=" limit "+to_string(limit_)+","+to_string(offset_); }
  return sql;
}
struct User{
  int32_t _id;
  string _account;
  string _pwd;
  string _name;
};User user{1,"lowne","gulp","swift"};
int main(){
  string ColList[10]={"id","created","updated","account","pwd","name","status","phone","photo","logged"};
  Sql<User>sq("select");
  string list=sq.limit(0).offset(10).field(ColList,Size(ColList))
  .orderBy("id",Sort::DESC).orderBy("pwd",Sort::ASC).findAll();
  cout<<list<<endl;
  return 0;
}