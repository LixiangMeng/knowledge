#include<iostream>
#include<atomic>
using namespace std;

template<typename T>
class Shared_ptr
{
private:
    T *ptr_;
    atomic<int> *count_;
public:
    Shared_ptr(T *p):count_(nullptr),ptr_(p){
        if(p){
            count_ = new atomic<int>(1);
        }
    }
    Shared_ptr(const Shared_ptr& other):count_(other.count_),ptr_(other.ptr_){
        if(count_){
            count_->fetch_add(1);
        }
    }

    Shared_ptr(Shared_ptr&& other) :count_(other.count_),ptr_(other.ptr_){
        other.ptr_ = nullptr;
        other.count_ = nullptr;
    }

    Shared_ptr& operator=(const Shared_ptr& other){
        if(this!=&other){
            if(count_&&count_->fetch_sub(1)==1){
                delete ptr_;
                delete count_;
            }
            ptr_ = other.ptr_;
            count_ = other.count_;
            count_->fetch_add(1);
        }
        return *this;
    }

    ~Shared_ptr(){
        //fetch_sub返回减少之前的�?
        if(count_&&count_->fetch_sub(1)==1){
            delete ptr_;
            delete count_;
        }
    }

    T* operator->() const {
        return ptr_;
    }
    
    T& operator*() const {
        return *ptr_;
    }

    int use_count() {
        return count_?count_->load():0;
    }
};

int main(){
    Shared_ptr<int> p1(new int(42));
    cout<<" p1 value: "<<*p1<<endl;
    cout<<" p1 count: "<<p1.use_count()<<endl;
    
    Shared_ptr<int> p2(p1);
    cout<<" p2 value: "<<*p2<<endl;
    cout<<" p1 count: "<<p1.use_count()<<endl;

    Shared_ptr<int> p3(std::move(p1));
    cout<<" p3 value: "<<*p3<<endl;
    cout<<" p2 count: "<<p2.use_count()<<endl;

    Shared_ptr<int> p4(new int(33));
    cout<<" p4 value: "<<*p4<<endl;
    cout<<" p4 count: "<<p4.use_count()<<endl;
    p4 = p3;

    cout<<" p4 value: "<<*p4<<endl;
    cout<<" p4 count: "<<p4.use_count()<<endl;
}