#include <gtest/gtest.h>

#include <myproject/message.h>
#include <myproject/cat.h>
#include <myproject/tie.h>

TEST(Message,Overfill){
    std::stringstream s;
    message(s,"% + % + % + % = %",15,20,30,4,"nice","BOY");

    EXPECT_EQ("15 + 20 + 30 + 4 = nice",s.str());   
}
TEST(Message,less){
    std::stringstream s;
    message(s,"% + % + % + % = %",15,20,30,4);

    EXPECT_EQ("15 + 20 + 30 + 4 = %",s.str());   
}

TEST(Cat,JustSomeTest){
    std::array<int,15> expected = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    auto actual = cat(std::array<int,5>{1,2,3,4,5},std::array<int,5>{6,7,8,9,10},std::array<int,5>{11,12,13,14,15});

    EXPECT_EQ(expected,actual);
}

TEST(TieTest,_){
    std::array<int,5> a = {1,2,3,4,5};
    std::array<int,5> b = {1,2,3,4,5};
    std::array<int,5> c = {1,2,3,4,5};
    my_tie(a,b,c) = std::array<int,15>{101,102,103,104,105,106,107,108,109,110,111,112,113,114,115};

    std::array<int,5> expected = {101,102,103,104,105};
    EXPECT_EQ(a,expected);
}