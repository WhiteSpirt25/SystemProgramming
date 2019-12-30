#include <iostream>


#include <ostream>

template <typename T>
class n_iter{
    const size_t _N;
    std::ostream& _stream;
    size_t _counter = 0;
public:

    n_iter(std::ostream& stream,const size_t& elem_num):_stream(stream),_N(elem_num){}
    
    n_iter& operator=(const T& elem){
        if (++_counter == _N){
            _stream<<elem;
            _counter = 0;
        }
        return *this;
    }
};
int main(){

    int arr[] = {1,2,3,4,5,6,7,8,9,10};

    n_iter<int> it(std::cout,4);
    for (size_t i = 0; i < 10; i++)
    {
        it = arr[i];
    }
    
    return 0;
}