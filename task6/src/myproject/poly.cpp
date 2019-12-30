#include <iostream>



#include <vector>
#include <complex>
#include <algorithm>

template <typename T>
class polynomial{
    std::vector<T> _coef;
public:
    // reverse нужен для классического ввода полиномов с убывающими степенями
    polynomial(std::initializer_list<T> ini):_coef(ini){
        std::reverse(_coef.begin(),_coef.end());
    }
    polynomial(std::vector<T> ini):_coef(ini){
        std::reverse(_coef.begin(),_coef.end());
    }
    polynomial(const size_t& size){
        _coef.resize(size);
    }
    polynomial(const polynomial& poly):_coef(poly._coef){}

    polynomial& operator=(const polynomial& poly){
        _coef = poly._coef;
        return *this;
    }

    polynomial operator*(const T& const_numb){
        
        auto temp = _coef;
        
        for (auto &elem : temp)
        {
            elem *= const_numb;
        }
        
        return polynomial(temp);
    }
    void print(){
        // Для убывающего порядка степеней выводится в обратном порядке
        for (int i = _coef.size() - 1; i >= 0; i--)
        {
            std::cout<<_coef[i]<<' ';
        }
        std::cout<<'\n';
        
    }
    const size_t deg() const {
        return _coef.size() - 1;
    }
    const T operator[](const size_t& i) const {
        return _coef[i]; 
    }
    T& operator[](const size_t& i){
        /*
        if (_coef.size() < i)
            _coef.resize(i);
        */
        return _coef[i]; 
    }
    
};

template<class T> struct is_complex : std::false_type {};
template<class T> struct is_complex<std::complex<T>> : std::true_type {};


template <typename T>
typename std::enable_if<!is_complex<T>::value,polynomial<T>>::type shur(const polynomial<T>& poly){
    const size_t n = poly.deg();
    polynomial<T> ans(n); // -1 уже учтено
    //std::cout<<"Real Shur\n";
    for (size_t i = 0; i < n; i++)
    {
        ans[i] = poly[0] * poly[i] - poly[n] * poly[n-i];
    }
    return ans;
}


template <typename T>
typename std::enable_if<is_complex<T>::value,polynomial<T>>::type shur(const polynomial<T>& poly){
    const size_t n = poly.deg();
    polynomial<T> ans(n);
    for (size_t i = 0; i < n; i++)
    {
        ans[i] = std::conj(poly[0]) * poly[i] - poly[n] * std::conj(poly[n-i]);
    }
    return ans;
}

int main(){

    using namespace std::complex_literals;

    std::complex<double> z1 = 2. + 3i, z2 = 7. - 8i, z3 = 1i, z4 = -10i, z5 = 6. + 9i;
    
    polynomial<std::complex<double>> zp = {z1,z2,z3,z4,z5};
    polynomial<float> p = {1,2,3,4,0.5};

    std::cout<<"Before shur:\n";
    zp.print();
    p.print();

    zp = shur(zp);
    p = shur(p);

    std::cout<<"After shur:\n";
    zp.print();
    p.print();


    std::cout<<"_____________________________";
    return 0;
}