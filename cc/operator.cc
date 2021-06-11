#include<iostream>
#include<string>
#include<vector>
using namespace std;
struct Vec{float x,y,z;
  Vec(float x,float y,float z):x(x),y(y),z(z){}
  Vec(const Vec&v):x(v.x),y(v.y),z(v.z){cout<<"~"<<endl;}
};
ostream&operator<<(ostream&s,const Vec&v){
  s<<v.x<<v.y<<v.z;return s;
}
void Function(const vector<Vec>&vertices){}
class Entity{
  public:int x;
  void Print()const{cout<<"Hello!"<<endl;}};
class ScopedPtr{
  private:Entity*e;
  public:ScopedPtr(Entity*_):e(_){

  }~ScopedPtr(){delete e;}
  Entity*operator->(){
    return e;
  }
  const Entity*operator->() const{
    return e;
  }
};

int main(){
  Entity e;e.Print();Entity*ptr=&e;ptr->Print();//(*ptr).Print();
  ptr->x=2;
  const ScopedPtr entity=new Entity();
  entity->Print();
  int offset=(int)&((Vec*)nullptr)->z;
  // Vec*vertex=new Vec[5];
  vector<Vec>vertices;
  vertices.emplace_back(1,2,3);
  vertices.emplace_back(4,5,6);
  // vertices.push_back({4,5,6});
  // vertices.push_back(Vec(7,8,9));
  Function(vertices);
  for (int i = 0; i < vertices.size(); i++)
    cout<<vertices[i]<<endl;
  vertices.erase(vertices.begin()+1);
  for (Vec&v:vertices) cout<<v<<endl;
  // vertices.clear();
  cin.get();
}