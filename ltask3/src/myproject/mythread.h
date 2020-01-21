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
    Func* func = reinterpret_cast<Func*>(arg);;
    int ret = 0;
    try{
    (*func)();
    }catch(...){
        ret = 1;
    }
    return ret;
}
class mythread{
    pid_t _pid = 0;
    std::unique_ptr<char> _stack;

public:
    mythread() = default;

    template<class Function>
    explicit mythread(Function f){
        // выделяю память
        size_t stack_size = 4096*2;
        //std::unique_ptr<char[]> child_stack(new char[stack_size]);
        _stack.reset(new char[stack_size]);

        // клонирую
        std::cout<<"Cloning..."<<"\n";


        CHECK(
        _pid = clone(child_main<Function>, _stack.get() + stack_size,
        CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_SYSVSEM | SIGCLD ,&f)
        );

        std::cout<<"Cloned\n";
    } 
    // move constructor
    mythread(mythread&& other):_pid(other._pid),_stack(std::move(other._stack)){
        std::cout<<"move constructor\n";
        other._pid = 0;
    }
    mythread(const mythread&) = delete;

    ~mythread(){
        if (_pid > 0) 
            std::cout<<"Killing thread\n";
            CHECK(kill(_pid,SIGTERM));
    }

    mythread& operator=(mythread&& thr){
        std::cout<<"operator=\n";
        swap(thr);
        return *this;
    }

    bool joinable() const noexcept{
        return _pid != 0;
    }

    void join(){
        std::cout<<"Join is called\n";
        if (joinable()){

            /*
            // реализация через waitpid
            int wstatus;
            CHECK(waitpid(_pid,&wstatus,0));
            if (WIFEXITED(wstatus)){
                _pid = 0;
                _stack.reset();
            }else{
                std::cout<<"waitpid broke\n";
            }
            */
            
            // через waitid
            siginfo_t wstatus;
            CHECK(waitid(P_PID,this->_pid,&wstatus,WEXITED));


            if (wstatus.si_code == CLD_EXITED){
                _pid = 0;
                _stack.reset();
            }else{
                std::cout<<"wait broke\n";
            }
            
        } else throw std::errc::invalid_argument;
    }

    pid_t get_id() const noexcept {
        return _pid;
    }

    void swap(mythread& thr){
        std::cout<<"swap\n";
        std::swap(_pid,thr._pid);
        std::swap(_stack,thr._stack);
    }


};
