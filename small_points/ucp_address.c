#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct ucp_address ucp_address_t;

int main()
{
    ucp_address_t *t = (ucp_address_t *)malloc(16);
	if (t != NULL) {
        printf("t %p\n", t);
		free(t);
	}
    return 0;
}
