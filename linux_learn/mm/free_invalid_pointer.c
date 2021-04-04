#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main()
{
    char * addr = malloc(16);
    if (NULL == addr)
    {
        printf("malloc failed \n");
	return 0;
    }

    free(addr + 1);
    return 0;
}
