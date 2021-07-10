#include <stdlib.h>
#include <stdio.h>
#include <string.h>


const int a = 1;


int main()
{
    // a = 2;
    
    printf("a = %d\n", a);
    const_add();
    printf("a = %d\n", a);
    return 0;
}
