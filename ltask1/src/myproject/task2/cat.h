#include <array>

template <class T, size_t N, class ... Tail> 
void cat(std::array<T,N>& res,size_t& last){
    // end of recursion
    return;
    }
 
template <class T, size_t M, size_t N, class ... Tail> 
void cat(std::array<T,M>& res,size_t& last,const std::array<T,N>& head,const Tail& ...tail ){
    // moving values from arg array named head
    for (int i = 0;i<head.size();++i){
        res[last] = std::move(head[i]);
        ++last;
    }
    // and recursive call
    cat(res,last,tail...);
}

template <class T, size_t Size, class ... Tail> 
auto cat(const std::array<T,Size>& head, const Tail& ...tail )
    -> std::array<T,Size * (sizeof...(tail)+1)>{
    // creation of output array and return after recursive walkthrough
    const size_t n = Size * (sizeof...(tail)+1);
    std::array<T,n> res;
    size_t last = 0;// how filled is res
    
    cat(res,last,head,tail...);

    return res;
} 
