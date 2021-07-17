#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int i = 0;
    int n = 20;
    int fib1 = 1; /* 迭代变量初始化 */
    int fib2 = 1;
    int fib = 0;

    if (n < 3) {
        return 1;
    }
    
    /* 循环体 */
    for (i = 3; i <= n; i++) {
        fib = fib1 + fib2; /* 迭代表达式 */
        fib1 = fib2; /* 迭代变量更新, 变量更新很容易出错 */
        fib2 = fib;
        printf("i %d, num %d\n", i, fib);
    }

    return 0;
}
