#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct test {
    int a;
    int b;
    int c;
    // int bc[]; // flexible array member not at end of struct, 没有指定元素个数的数组只能在结构体的最后边的位置
    int d;
    int e[];
};


// 数组，之前的概念是说的，编译的时候就需要确定数组的大小
// 但是在这里，一维数组不指定长度，也不初始化元素个数，
// 二维数组只指定列的个数，不指定行的个数，也没有初始化元素，这个样编译也不报错
// 虽然这样不报错，但是这样使用是不规范的，这样使用，编译为什么不报错呢 ???
int a[];
int b[][8];
int main()
{
    int c[] = {1, 2, 3};
    int d[][8] = {1, 2, 3, 1, 2, 3, 1, 2, 3}; // 这样会自动把第一行填满之后再开始第二行
    // printf("sizeof(a) %d\n", sizeof(a));
    printf("sizeof(c) %d, sizeof(d) %d\n", sizeof(c), sizeof(d));
    printf("sizeof(struct test) %d\n", sizeof(struct test));
    struct test *test0 = (struct test *)malloc(sizeof(struct test));
    if (test0 == NULL) {
        printf("malloc for test0 failed\n");
        return 0;
    }

    printf("test0 %p\n", test0);
    printf("e %p\n", test0->e);
    printf("0 a %p\n", a);
    a[1] = 0;
    printf("1 a %p, a[1] %d\n", a, a[1]);
    for (int i = 0; i < 10; i++) {
        a[i] = i;
        printf("i %d, val %d\n", i, a[i]);
    }
    return 0;
}
