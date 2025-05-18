#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
class Observer {
public:
    virtual void update(const string& message) = 0;
    virtual ~Observer() {}
};

class ConcreteObserver : public Observer {
    public:
    ConcreteObserver(const std::string& name) : name(name) {}
    void update(const string& message) {
        cout<<name<<" received message: "<<message<<endl;
    }
    private:
    string name;
};

class Subject {
public:
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* Observer) = 0;
    virtual void notify(const string& message) = 0;
    virtual ~Subject() {}
};

class ConcreteSubject {
public:
    void attach(Observer* observer){
        observers.push_back(observer);
    }
    void detach(Observer* observer){
        observers.erase(remove(observers.begin(),observers.end(),observer),observers.end());
    }
    void notify(const string& message){
        for(auto& observer:observers){
            observer->update(message);
        }
    }
private:
    vector<Observer*> observers;
};


int main(){
    ConcreteObserver observer1("test 1");
    ConcreteObserver observer2("test 1");

    ConcreteSubject subject;
    subject.attach(&observer1);
    subject.attach(&observer2);

    subject.notify("hello observers");

    subject.detach(&observer1);
    subject.notify("Observer 1 has been removed.");
}