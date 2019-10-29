#include <ostream>
#include <string>

#include <iostream>
#include <vector>



void message(std::ostream& stream,const char* str){
    stream<<*str;
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


int main(){
    
    message(std::cout,"% + % + % - % * %%",5,3,"dog","cat",5.8,"flies");

    return 0;
}