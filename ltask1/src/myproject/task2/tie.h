#include <iostream>


#include <array>
#include <vector>
#include <functional>

/*
// DANGEROUS OLD CODE I DON'T WANT TO DELETE YET
template<class T, size_t Size, size_t Amount, class ... Tail>
struct Tie {
    std::tuple<std::array<T,Size>&,Tail& ...> contents;

    Tie(std::tuple<std::array<T,Size>&,Tail&...> args){
        contents = args;
    }
    Tie(std::tuple<std::array<T,Size>&> args){
        contents = args;
    }
    // changes value of contents (variable which reference saved in this) to given array
    void operator=(const std::array<T,Size*Amount>& rhs){

    }
};

template<class T, size_t Size, class ... Tail> 
auto my_tie( std::array<T,Size>& head, Tail& ...tail ){

    //std::array<T,Size> size_finder = first_of_tail(tail...);

    // creates reference to given variable and returns Tie with that reference saved in
    std::tuple<std::array<T,Size>&,Tail&...> temp = std::forward_as_tuple(head,tail...);
    auto temp2 = Tie<T,Size,sizeof...(tail)+1,Tail ...>(temp);

    return temp2;
} 
*/

template <class T, size_t Size, size_t Amount>
struct Tie
{
    std::array<std::reference_wrapper<std::array<T, Size>>, Amount> contents;
    //std::reference_wrapper<std::array<T, Size>> contents[Amount];
    

    Tie(std::array<std::reference_wrapper<std::array<T, Size>>, Amount> args): contents(args){}
    

    // changes value of contents (variable which reference saved in this) to given array
    void operator=(const std::array<T, Size * Amount> &rhs)
    {

        for (size_t i = 0; i < Amount; i++)
        {
            for (size_t j = 0; j < Size; j++)
            {
                //std::cout<<(*contents)[i].get()[j];
                contents[i].get()[j] = rhs[i * Size + j];
            }
        }
    }
};

template <class T, size_t Size, class... Tail>
auto my_tie(std::array<T, Size> &head, Tail &... tail)
    -> Tie<T, Size, sizeof...(tail) + 1>
{
    /*
    std::vector<std::reference_wrapper<std::array<T,Size>>> v; // TODO:use array
    v.push_back(std::ref(head));

    using swallow = int[];
    swallow{0,(v.push_back(std::ref(tail)),0)...};//TODO: use array init = {std::ref(tail)...}
    */
    //________________________________________

    const auto amount = sizeof...(tail) + 1;

    std::array<std::reference_wrapper<std::array<T, Size>>, amount> arr = {std::ref(head), std::ref(tail)...};

    //std::reference_wrapper<std::array<T, Size>> arr [amount] = {std::ref(head), std::ref(tail)...};

    return Tie<T, Size, amount>(arr);
}
