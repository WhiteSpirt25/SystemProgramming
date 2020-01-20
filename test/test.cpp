#include <iostream>

class test{
    int attr  = 0;
public:
    void this_change(int i){
        this->attr = i;
    }
    void change(int i ){
        attr = i;
    }
    int get(){
        return attr;
    }
    int this_get(){
        return this->attr;
    }
};
int main(){

    test a;
    a.change(7);
    std::cout<<a.get()<<'\n';

    std::cout<<a.this_get()<<'\n';

    a.this_change(10);
    std::cout<<a.get()<<'\n';
    //______________________
    test b;

    std::cout<<b.get()<<'\n';

    std::cout<<b.this_get()<<'\n';

    b.change(7);
    std::cout<<b.get()<<'\n';

    std::cout<<b.this_get()<<'\n';

    b.this_change(10);
    std::cout<<b.get()<<'\n';


    std::cout<<b.this_get()<<'\n';
    

    return 0;
}