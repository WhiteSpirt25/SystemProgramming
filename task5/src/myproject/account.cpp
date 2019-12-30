#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>



#include <string>

struct account{
    std::string _name;
    int _id;

    account(const int& id, const std::string& name):_id(id),_name(name){}

    bool operator<(const account& acc) const {
        return _id < acc._id;
    }
    bool operator==(const account& acc) const {
        return _name==acc._name && _id == acc._id;
    }
};
namespace std {

  template <>
  struct hash<account>
  {
    std::size_t operator()(const account& acc) const
    {
      // Compute individual hash values,
      // and combine them using XOR
      // and bit shifting:

      return ((hash<string>()(acc._name)
               ^ (hash<int>()(acc._id) << 1)));
    }
  };

}
    
int main(){
    std::map<account,int> map;
    std::unordered_map<account,int> umap;
    std::set<account> set;
    std::unordered_set<account> uset;

    map[account(1,"Peter")]= 10;

    return 0;
}