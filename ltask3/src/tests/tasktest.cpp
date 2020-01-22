#include <iostream>
#include <unistd.h> // sleep

#include <algorithm>

#include "../myproject/mythread.h"
#include <thread>
#include <vector>
#include <mutex>

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

void thread_merge(std::mutex& m,std::vector<int>& main_vec,std::vector<int> v){
    auto sorted = break_and_merge(v);
    const std::lock_guard<std::mutex> lock(m);
    main_vec = merge(main_vec,sorted);
}
auto my_merge_sort(std::vector<int> v){

    // number of streams or elements in array if less
    const size_t cores = 
        std::thread::hardware_concurrency();
    // number of elements in split
    const unsigned int part_size = v.size() / cores; 

    std::vector<mythread> threads;
    std::vector<int> ans;
    std::mutex m;
    /*
    // every stream takes part of vector
    for (size_t i = 0; i < cores -1; i++)
    {
       threads.emplace_back(
           [&m,&ans,&v,part_size,i](){
            thread_merge(std::ref(m), std::ref(ans), slice(v,part_size * i,part_size * (i+1)));
            return 0;
           }
        );
    }
    // the last one takes everething that left after splitting
    threads.emplace_back(
        [&m,&ans,&v,part_size,cores](){
        thread_merge(std::ref(m), std::ref(ans), slice(v,part_size * (cores-1), v.size()));
        return 0;
        }
    );

    for (size_t i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }
    */

    mythread thread1(
           [&m,&ans,&v,part_size](){
            thread_merge(std::ref(m), std::ref(ans), slice(v,part_size * 0,part_size * (0+1)));
            return 0;
           });
    mythread thread2(
           [&m,&ans,&v,part_size](){
            thread_merge(std::ref(m), std::ref(ans), slice(v,part_size * 1,part_size * (1+1)));
            return 0;
           });
    mythread thread3(
           [&m,&ans,&v,part_size](){
            thread_merge(std::ref(m), std::ref(ans), slice(v,part_size * 2,part_size * (2+1)));
            return 0;
           });
    mythread thread4(
           [&m,&ans,&v,part_size](){
            thread_merge(std::ref(m), std::ref(ans), slice(v,part_size * 3,v.size()));
            return 0;
           });
    
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    std::cout<<"Returning answer\n";
    return ans;

}
int RandomNumber () { return (std::rand()%100); }
void print_vec(const std::vector<int>& vec){
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout<<vec[i]<<' ';
    }
    std::cout<<std::endl;
}
int test_fun(){
   return 0; 
}
int main(){
    
    
    mythread test(test_fun);
    test.join();
    return 0;

    
    /*
    // testing my thread with simple functions
    int a = 125;
    int b = 377;
    std::vector<mythread> test;
    test.emplace_back([&a](){std::cout<<++a<<" 1 thread\n";});
    test.emplace_back([&b](){std::cout<<++b<<" 2 thread\n";});

    for (size_t i = 0; i < test.size(); i++)
    {
        std::cout<<"Joining thread# "<<i<<'\n';
        test[i].join();
    }

    std::cout<<a<<b<<"\n__________";

    return 0;
    */
    /*
    std::vector<int> vec ;
    std::vector<std::chrono::duration<double>> time;
    std::vector<std::chrono::duration<double>> time1;

    const int N = 5;
    const int step_size = 100;

    for (size_t i = 1; i < N; i++)
    {

        vec.resize(step_size*i);
        //std::cout<<vec.end() - vec.begin()<<'\n';
        std::generate (vec.begin(), vec.end(), RandomNumber);

        auto start = std::chrono::system_clock::now();
        auto res = my_merge_sort(vec);
        auto end = std::chrono::system_clock::now();


        auto start1 = std::chrono::system_clock::now();
        auto res1 = break_and_merge(vec);
        auto end1 = std::chrono::system_clock::now();
        
        
        std::sort(vec.begin(),vec.end());

        if (vec != res){
            std::cout<<"Not sorted, fix bugs\n";

            std::cout<<res.size()<<'\n';
            print_vec(res);    
            
        }
        if (res1 != res){
            std::cout<<"Thread different from threads\n";
        }

        time.emplace_back(end-start);
        time1.emplace_back(end1-start1);     

        
        std::cout<<"Passed "<<i<<" \n\n";   
        
    }

    for (int i = 1;i<N;i++)
    {
        std::cout<<"Size: "<<i*step_size<<" Time: "<<time[i-1].count()<<" Time with 1 thread: "<<time1[i-1].count()<<'\n';
    }
    

    return 0;
    */
}