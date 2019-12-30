#include <ostream>

struct MyGuard
{
    std::ostream &_x;
     
    std::ios_base::fmtflags fl;
    char fill;
    std::ios_base::iostate exc;
    
    MyGuard(std::ostream &x) : _x(x)
    {
        // сохранил флаги, символ заполнения и маску исключений для последующего их восстановления
        fl = x.flags(); 
        fill = x.fill(); 
        exc = x.exceptions();
    }
    ~MyGuard()
    {
        _x.flags(fl);
        _x.fill(fill);
        _x.exceptions(exc);
    }
};