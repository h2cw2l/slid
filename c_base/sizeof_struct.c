#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct test {
    int a;
    int b;
    int c;
    // int bc[]; // flexible array member not at end of struct, 没有指定元素个数的数组只能在结构体的最后边的位置
    int d;
    int e[1];
};

int a[];

int main()
{
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
    for (int i = 0; i < 8192; i++) {
        a[i] = i;
        printf("i %d, val %d\n", i, a[i]);
    }
    return 0;
}
