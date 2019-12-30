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

class trait{
public:
    template <typename T>
    static int size(const circle<T>& obj){
        return sizeof(circle<T>);
    }
    template <typename T>
    static int size(const rect<T>& obj){
        return sizeof(rect<T>);
    }
};
int main(){

    circle<double> c(10);

    rect<float> r(20,10);

    std::cout<<"Size of circle: "<<trait::size(c)<<'\n';
    std::cout<<"Size of rectangle: "<<trait::size(r)<<'\n';


    return 0;
}