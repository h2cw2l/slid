#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern int a;

int const_add()
{
    printf("add function a %d\n", a);
    // a++;
    int *b = &a;
    *b = 10;
    printf("after function add a %d\n", a);
    return 0;
}
