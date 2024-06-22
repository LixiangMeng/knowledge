#include<iostream>
using namespace std;


//����ģʽ:�������ʱ�򴴽����������̰߳�ȫ
class SinInstance
{
private:
    //2.���Ӿ�̬˽�еĵ�ǰ���ָ�����
    static SinInstance* sin;
    //1.��Ҫ���û������������ù��캯��
    SinInstance(){}
public:
    //3.�ṩ��̬����ӿڣ��������û���õ�������
    static SinInstance* getInstance(){
        return sin;
    }
    void print(){
        cout<<"����ģʽ����������"<<endl;
    }
    
};
//��̬��Ա����������ڲ����г�ʼ��,�Ե����Ķ�����г�ʼ��
SinInstance* SinInstance::sin = new SinInstance;

//����ģʽ��ʲôʱ��ʹ���������ģʽ����ʹ�õ�ʱ����ȥ������Ӧ��ʵ��
class SingletonLazy 
{
private:
    //2.���Ӿ�̬˽�еĵ�ǰ���ָ�����
    static SingletonLazy* sin2;
    //1.��Ҫ���û������������ù��캯��
    SingletonLazy(){}
public:
    //3.�ṩ��̬����ӿڣ��������û���õ�������
    static SingletonLazy* getInstance(){
        if(sin2==nullptr){
            sin2 = new SingletonLazy;
        }
        return sin2;
    }
    void print(){
        cout<<"����ģʽ����������"<<endl;
    }
};
SingletonLazy* SingletonLazy::sin2 = nullptr;


int main(){
    //ͨ�������õ�ʵ������
    SinInstance* tmp = SinInstance::getInstance();
    SingletonLazy* tmp2 = SingletonLazy::getInstance();
    tmp->print();
    tmp2->print();
}