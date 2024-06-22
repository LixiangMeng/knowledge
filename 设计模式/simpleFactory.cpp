#include<iostream>
using namespace std;

//1.��Ʒ�ĸ���
class AbstractSmile
{
public:
    virtual void transform() = 0;
    virtual void ability() = 0;
    virtual ~AbstractSmile(){}
};

//2.��Ʒ������
class SheepSmile: public AbstractSmile
{
public:
    void transform() override{
        cout<<"sheep transform"<<endl;
    }

    void ability(){
        cout<<"sheep ability"<<endl;
    }

};

class LionSmile: public AbstractSmile
{
public:
    void transform() override{
        cout<<"Lion transform"<<endl;
    }

    void ability(){
        cout<<"Lion ability"<<endl;
    }

};

//3.���幤����
enum class Type:char{Sheep,Lion,Bat};
class SmileFactory
{
public:
    AbstractSmile* createSmile(Type type){
        AbstractSmile* ptr = nullptr;
        switch (type)
        {
        case Type::Sheep:
            ptr = new SheepSmile;
            break;
        case Type::Lion:
            ptr = new LionSmile;
            break;
        default:
            break;
        }
        return ptr;
    }
};

int main(){
    SmileFactory* factory = new SmileFactory;
    AbstractSmile* obj= factory->createSmile(Type::Lion);
    obj->transform();
    obj->ability();
}