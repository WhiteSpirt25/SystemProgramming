#include <system_error>
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
{ \
    if ((func) == -1) { \
        throw std::system_error(errno, std::generic_category()); \
    } \
}
template <class Func>
static int child_main(void* arg){
    Func* func = reinterpret_cast<Func*>(arg);
    int ret = 0;
    (*func)();
    return ret;
}
class mythread{
    pid_t _pid = 0;
    std::unique_ptr<char[]> _stack;


public:
    mythread() = default;

    template<class Function>
    explicit mythread(Function& f){
        // выделяю память
        const size_t stack_size = 1024*1024;
        //std::unique_ptr<char[]> child_stack(new char[stack_size]);
        _stack.reset(new char[stack_size]);
        
        _pid = clone(child_main<Function>, _stack.get() + stack_size-1,
        CLONE_VM | SIGCHLD  ,&f);
        CHECK(_pid);
        
    } 
    // move constructor
    mythread(mythread&& other):_pid(other._pid),_stack(std::move(other._stack)){
        other._pid = 0;
    }
    mythread(const mythread&) = delete;

    ~mythread(){
        if (_pid > 0) {
            CHECK(kill(_pid,SIGTERM));
        }
        _stack.reset();
    }

    mythread& operator=(mythread&& thr){
        swap(thr);
        return *this;
    }

    bool joinable() const noexcept{
        return _pid != 0;
    }

    void join(){
        if (joinable()){

            //std::cout<<"Joining\n";
            // реализация через waitpid
            int wstatus;
            CHECK(waitpid(_pid,&wstatus,0));
            //std::cout<<"waited\n";
            if (WIFEXITED(wstatus)){
                _pid = 0;
                //std::cout<<"Join:resseting\n";
                _stack.reset();
                //std::cout<<"Join:after reset\n";
                
            }else{
                std::cout<<"waitpid broke\n";
            }
            
            
        } else throw std::errc::invalid_argument;
    }

    pid_t get_id() const noexcept {
        return _pid;
    }

    void swap(mythread& thr){
        std::swap(_pid,thr._pid);
        std::swap(_stack,thr._stack);
    }


};
