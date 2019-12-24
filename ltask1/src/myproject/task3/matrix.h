#include <vector>
#include <math.h>

template <class T>
struct Matrix
{
    std::vector<T> data;
    size_t size;

    Matrix() {}
    Matrix(std::vector<T>&& v){
        data = std::move(v);
        size = sqrt(data.size());
    }

    Matrix &operator=(const Matrix &mat)
    {
        data = mat.data;
        size = mat.size;
        return *this;
    }
    Matrix &operator=(std::vector<T> &&v)
    {
        data = std::move(v);
        size = sqrt(data.size());
        return *this;
    }
    void set_size(const int n)
    {
        data.resize(int(n * n));
        size = n;
    }
    const Matrix<char> operator<(const Matrix &mat)
    {

        Matrix<char> ans;
        ans.set_size(mat.size);

        for (size_t row = 0; row < size; row++)
        {
            for (size_t col = 0; col < size; col++)
            {
                ans(row, col) = this->operator()(row, col) < mat(row, col);
            }
        }
        return ans;
    }
    const Matrix<char> operator<(const T eps) const
    {

        Matrix<char> ans;
        ans.set_size(size);

        for (size_t row = 0; row < size; row++)
        {
            for (size_t col = 0; col < size; col++)
            {
                ans(row, col) = this->operator()(row, col) < eps;
            }
        }
        return ans;
    }
    T &operator()(const size_t &row, const size_t &col)
    {
        return data[row * size + col];
    }
    T operator()(const size_t row, const size_t col) const
    {
        return data[row * size + col];
    }
    const Matrix operator-(const Matrix &mat) const
    {
        Matrix temp = *this;

        for (size_t row = 0; row < size; row++)
        {
            for (size_t col = 0; col < size; col++)
            {
                temp(row, col) -= mat(row, col);
            }
        }

        return temp;
    }
    
    bool is_symmetric() const {
        const float eps = 0.00001;
        return all(abs(*this - this->transposed()) < eps);
    }
    
    const Matrix transposed() const
    {
        Matrix temp = *this;

        for (size_t i = 0; i < size; i++)
        {
            for (size_t col = 0; col < size; col++)
            {
                temp(i, col) = this->operator()(col, i);
            }
        }

        return temp;
    }
    
    bool operator==(const Matrix& mat)const{
        return data == mat.data;
    }
};
template <class T>
const Matrix<T> where(const Matrix<char> &bmat, const Matrix<T> &a, const Matrix<T> &b)
{
    Matrix<T> ans;
    ans.set_size(bmat.size);

    for (size_t row = 0; row < bmat.size; row++)
    {
        for (size_t col = 0; col < bmat.size; col++)
        {
            if (bmat(row, col))
            {
                ans(row, col) = a(row, col);
            }
            else
            {
                ans(row, col) = b(row, col);
            }
        }
    }

    return ans;
}
template <class T>
const Matrix<T> abs(const Matrix<T> &mat)
{
    Matrix<T> temp = mat;

    for (size_t row = 0; row < temp.size; row++)
    {
        for (size_t col = 0; col < temp.size; col++)
        {
            temp(row, col) = abs(temp(row, col));
        }
    }

    return temp;
}

bool all(const Matrix<char> &mat)
{

    for (size_t row = 0; row < mat.size; row++)
    {
        for (size_t col = 0; col < mat.size; col++)
        {
            if (!mat(row, col))
                return false;
        }
    }

    return true;
}
