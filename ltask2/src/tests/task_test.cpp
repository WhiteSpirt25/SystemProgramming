#include <gtest/gtest.h>
#include <myproject/vector2d.h>

struct rot_param
{
    vector2d input_vec;
    int input_ang;
    vector2d expected_output;
};
class rot_test : public ::testing::TestWithParam<rot_param>
{
};

TEST_P(rot_test, _)
{
    const rot_param &param = GetParam();

    EXPECT_EQ(param.expected_output, rot(param.input_vec, param.input_ang));
}

INSTANTIATE_TEST_CASE_P(_, rot_test, ::testing::Values(
    rot_param{
            vector2d(18,3), 270, vector2d(-3,18)
        }, 
    rot_param{
            vector2d(-135,-48), 810, vector2d(-48,135)
        }, 
    rot_param{
            vector2d(1111.11,132135465.18), 720, vector2d(1111.11,132135465.18 )
        }, 
    rot_param{
            vector2d(183,-24), 180, vector2d(-183,24)
        }
    )
);
