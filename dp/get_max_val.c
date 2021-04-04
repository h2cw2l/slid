#include "stdlib.h"
#include "stdio.h"
#include "string.h"

int a[10] = {10, 5, 6, 20, 60, 77, 1, 10, 20, 30};

int main()
{
    printf("sizeof(array) %d \n", sizeof(a));
    int max_val = 0;
    int min_val = 10000;

    for (int i = 0; i < 10; i++)
    {
        if (a[i] > max_val)
        {
	    max_val = a[i];
	}

	if (a[i] < min_val)
	{
	    min_val = a[i];
	}
    }

    printf("max %d, min %d \n", max_val, min_val);
    return 0;
}
