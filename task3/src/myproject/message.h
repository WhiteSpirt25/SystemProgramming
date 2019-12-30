#include <ostream>
#include <iostream>
#include <vector>



void message(std::ostream& stream,const char* str){
    while(*str){
        stream<<*str;
        ++str;
    }
}
template<class Head ,class ... Tail>
void message(std::ostream& stream,const char* str,const Head& head ,const Tail& ...tail){
    
    while (*str){
        if (*str == '%'){
            stream<<head;
            message(stream,str+1,tail...);
            return;
        }
        
        stream<<*str;
        ++str;

    }    
}
