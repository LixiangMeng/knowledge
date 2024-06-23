
#include <iostream>
using namespace std;

void print(int& lvalue,int&& rvalue){
    cout<<"lvalue:"<<lvalue<<endl;
    cout<<"rvalue:"<<rvalue<<endl;
}

class Myobject
{
private:
    /* data */
public:
    Myobject() = default;
    Myobject(Myobject&& object){
        cout<<"调用了移动构造函数"<<endl;
    }
    Myobject&  operator=(Myobject&& object){
        cout<<"调用了移动赋值运算符"<<endl;
        return *this;
    }
    ~Myobject(){
        cout<<"调用了析构函数"<<endl;
    }
};


int main(){
    // int a = 1;
    // print(a,std::move(a));
    Myobject obj1;
    Myobject obj2 = move(obj1);
    Myobject obj3;
    obj3 = move(obj2);
}