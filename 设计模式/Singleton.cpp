#include<iostream>
using namespace std;


//饿汉模式:定义类的时候创建单例对象，线程安全
class SinInstance
{
private:
    //2.增加静态私有的当前类的指针变量
    static SinInstance* sin;
    //1.不要让用户在类的外面调用构造函数
    SinInstance(){}
public:
    //3.提供静态对外接口，可以让用户获得单例对象。
    static SinInstance* getInstance(){
        return sin;
    }
    void print(){
        cout<<"饿汉模式，单例对象"<<endl;
    }
    
};
//静态成员不能在类的内部进行初始化,对单例的对象进行初始化
SinInstance* SinInstance::sin = new SinInstance;

//懒汉模式：什么时候使用这个单例模式，在使用的时候再去创建对应的实例
class SingletonLazy 
{
private:
    //2.增加静态私有的当前类的指针变量
    static SingletonLazy* sin2;
    //1.不要让用户在类的外面调用构造函数
    SingletonLazy(){}
public:
    //3.提供静态对外接口，可以让用户获得单例对象。
    static SingletonLazy* getInstance(){
        if(sin2==nullptr){
            sin2 = new SingletonLazy;
        }
        return sin2;
    }
    void print(){
        cout<<"懒汉模式，单例对象"<<endl;
    }
};
SingletonLazy* SingletonLazy::sin2 = nullptr;


int main(){
    //通过类名得到实例对象
    SinInstance* tmp = SinInstance::getInstance();
    SingletonLazy* tmp2 = SingletonLazy::getInstance();
    tmp->print();
    tmp2->print();
}