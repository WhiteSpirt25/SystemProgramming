#include <iostream>

template <typename T>
class circle{
    T _radius;
public:
    circle(const T& radius):_radius(radius){}
    
    const T get_radius() const {
        return _radius;
    }
};
template <typename T>
class rect{
    T _length;
    T _width;
public:
    rect(const T& length, const T& width):_length(length),_width(width){}
    
    const T get_length() const {
        return _length;
    }
    const T get_width() const {
        return _width;
    }
};
template <typename T>
class trait{
    static int size(const circle<T>& obj){
        return sizeof(T);
    }
    static int size(const rect<T>& obj){
        return 2*sizeof(T);
    }
};
int main(){



    return 0;
}