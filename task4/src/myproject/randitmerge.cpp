#include <iostream>

#include <vector>

auto slice(const std::vector<int>& v , const size_t begin, const size_t end){
    // returns slice (part) of a vector from begin to end
    std::vector<int>::const_iterator first = v.begin() + begin;
    std::vector<int>::const_iterator last = v.begin() + end;
    std::vector<int> newVec(first, last);
    return newVec;
}
auto merge(const int& a, const int& b){
    // creates container with out of 2 sorted elements
    std::vector<int> ans;
    if (a < b){
        ans.push_back(a);
        ans.push_back(b);
    } else {
        ans.push_back(b);
        ans.push_back(a);
    }
    return ans;
}
auto merge(const std::vector<int>& v1,const std::vector<int>& v2){
    // merges 2 sorted containers together into one 
    std::vector<int> ans;
    auto it1 = v1.begin();
    auto it2 = v2.begin();
    while (it1 != v1.end() && it2 != v2.end()){
        if(*it1 < *it2){
            ans.push_back(*it1);
            ++it1;
        } else{
            ans.push_back(*it2);
            ++it2;
        }
    }
    // add last elements from not finished container
    while(it1 != v1.end()){
        ans.push_back(*it1);
        ++it1;
    }
    while(it2 != v2.end()){
        ans.push_back(*it2);
        ++it2;
    }
    return ans;
}
auto break_and_merge(std::vector<int> v){
    // returns sorted vector by recursively breaking it down and merging together 
    switch (v.size())
    {
    case 1:
        return v;
    case 2:
        return merge(v[0],v[1]);    
    default:
        return merge(break_and_merge(slice(v,0,v.size()/2)),
            break_and_merge(slice(v,v.size()/2,v.size())));
    }
}
int main(){

    std::vector<int> a = {5,7,6,2,1,5,6,3,21,1,2,3,5,9};

    a = break_and_merge(a);

    for (size_t i = 0; i < a.size(); i++)
    {
        std::cout<<a[i]<<' ';
    }
    
    
    return 0;
}