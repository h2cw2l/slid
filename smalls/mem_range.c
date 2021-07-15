#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// 32位 user 0x00000000 ~ 0xc0000000 kerney 0xc0000000 0xffffffff
// 64位 user 0x0000000000000000 ~ 0x00007ffffffff000 kernel 0xffff800000000000 ~ 0xffffffffffffffff
int main()
{
    int a = 0;
    int *b = (int *)malloc(sizeof(int) * 16);
    printf("&a %p, b 0x%lx\n", &a, b);
    long *la = (long *)(void *)(/*0xffff800000008000*/ /* (unsigned long)(void *)b + 4096 */ 0xffffffffa5fbe820);
    // *la = 10;
    printf("la %ld\n", *la);
    return 0;
}
