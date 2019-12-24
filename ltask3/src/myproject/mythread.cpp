#include <iostream>

// check 
#include <sched.h>
// pid
#include <sys/types.h>
// kill
#include <signal.h>
// unique_ptr
#include <memory>
// waitpid
#include <sys/wait.h>
// getpid
#include <unistd.h>
// std::function
#include <functional>

#define CHECK(func) \
    if((func) == -1) {\
        throw std::system_error(errno, std::generic_category()); \
    }

void some_func(){
    for (size_t i = 0; i < 10; i++)
    {
        std::cout<<i<<"\n";
    }
    
}

class mythread{
    pid_t _pid = 0;

public:
    mythread(){}

    template<class Function>
    mythread(Function f){
        // выделяю память
        size_t stack_size = 1024*10;
        std::unique_ptr<char[]> child_stack(new char[stack_size]);
        
        // клонирую
        std::cout<<"Cloning..."<<"\n";


        CHECK(
        _pid = clone(f, child_stack.get() + stack_size,
        CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_SYSVSEM | SIGCLD ,0)
        );
    } 
    
    ~mythread(){
        kill(_pid,SIGTERM);
    }

    mythread& operator=(mythread&& thr){
        swap(thr);
    }

    bool joinable() const noexcept{
        return _pid != 0;
    }

    void join(){
        if (joinable()){
            CHECK(waitpid(_pid,NULL,0));
        } else throw std::errc::invalid_argument;
    }

    pid_t get_id() const noexcept {
        return _pid;
    }

    void swap(mythread& thr){
        std::swap(_pid,thr._pid);
    }


};


int main(){

    int a = 5;

    mythread thr([a](void* arg){some_func();return 0;});
    thr.join();

    std::cout<<"\n____________________\n";
    return 0;
}
