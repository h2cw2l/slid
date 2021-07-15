#include <gtest/gtest.h>
// https://blog.csdn.net/qq_36251561/article/details/85319547

int Foo(int a, int b)
{
    if (a == 0 || b == 0) {
        throw "don't do that";
    }
    
    printf("a %d, b %d\n", a, b);    
    int c =  a % b;
    if (c == 0) {
        return b;
    }

    return Foo(b, c);
}

TEST(FooTEST, HandleNoneZeroInput)
{
    EXPECT_EQ(2, Foo(4,10));
    EXPECT_EQ(6, Foo(30,18));
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
