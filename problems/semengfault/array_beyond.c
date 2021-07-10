#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// int a[10] = {0};
int main()
{
    int a[10] = {0};

    for (int i = 0; i < 11; i++) {
        printf("i %d\n", i);
        a[i] = i;
    }
    sleep(1);
    return 0;
}
