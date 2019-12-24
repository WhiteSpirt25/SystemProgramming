#include <gtest/gtest.h>
#include <myproject/matrix.h>

//___________________________GUARD TEST_____________________________________

#include <myproject/myguard.h>

void print_hex(std::ostream& stream,  int i)
{
    MyGuard g(stream);
    stream.setf(std::ios_base::hex, std::ios_base::basefield);
    stream.fill('&');
    stream.exceptions(std::ostream::failbit);
    //или std::cout << std::hex
    stream << i;
}

TEST(Guard,_){
    std::stringstream s,exp;
    
    print_hex(s,125);

    EXPECT_EQ(std::make_tuple(s.flags(),s.fill(),s.exceptions()),
        std::make_tuple(exp.flags(),exp.fill(),exp.exceptions()));   
}


//___________________________WHERE TEST____________________________________

struct where_param
{
    Matrix<char> input1;
    Matrix<float> input2, input3;

    Matrix<float> expected_output;
};
class where_test : public ::testing::TestWithParam<where_param>
{
};

TEST_P(where_test, _)
{
    const where_param &param = GetParam();

    EXPECT_EQ(param.expected_output, where(param.input1, param.input2, param.input3));
}

Matrix<float> a (std::vector<float>{1,2,3,4,2,4,3,1,5});
Matrix<float> b (std::vector<float>{1,4,2,6,8,6,2,4,3});
Matrix<float> c (std::vector<float>{9,5,7,5,2,1,46,3,21});
Matrix<float> d (std::vector<float>{3,5,4,78,9,5,2,1,45});

INSTANTIATE_TEST_CASE_P(_, where_test, ::testing::Values(
    where_param{
        a < b , a , b , Matrix<float>(std::vector<float>{1,2,2,4,2,4,2,1,3})
        }, 
    where_param{
        c < d , c , d , Matrix<float>(std::vector<float>{3,5,4,5,2,1,2,1,21})
        }
    )
);

//__________________________IS SYMMETRIC TEST__________________________________________________________
struct sym_param
{
    Matrix<float> input;

    bool expected_output;
};
class sym_test : public ::testing::TestWithParam<sym_param>
{
};

TEST_P(sym_test, _)
{
    const sym_param &param = GetParam();

    EXPECT_EQ(param.expected_output, param.input.is_symmetric());
}

INSTANTIATE_TEST_CASE_P(_, sym_test, ::testing::Values(
    sym_param{
        Matrix<float>(std::vector<float>{1,2,3,4,5,6,7,8,9}) , false
        }, 
    sym_param{
        Matrix<float>(std::vector<float>{
            1,2,3,4,
            2,0,8,9,
            3,8,0,7,
            4,9,7,0}) , true
        }
    )
);