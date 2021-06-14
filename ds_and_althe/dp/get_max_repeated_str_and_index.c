#include "stdlib.h"
#include "stdio.h"
#include "string.h"

char *gstr = "abcdafffmmmlmnabcdabcdafffmmm";
struct result
{
    int idx;
    int len;
    int idxo;
};

struct result *get_max_len_repeated_str_and_its_idx(char *str)
{
    struct result * ret;
    int len;
    
    if (str == NULL)
    {
	    printf("str is null\n");
        exit(-1);
    }

    ret = (struct result *)malloc(sizeof(struct result));
    if (ret == NULL)
    {
	    printf("malloc for ret failed\n");
        exit(-1);
    }

    ret->idx = 0;
    ret->len = 0;
    ret->idxo = 0;

    len = strlen(str);
    printf("str len %u, str[0] = %c\n", len, str[0]);

    int i = 0;
    int j = 0;
    int k = 0;
    int idx_tmp = 0;
    int len_tmp = 0;
    
    for (i = 0; i < len - 1; i++)
    {
	    idx_tmp = 0;
	    len_tmp = 0;
	    k = 0;
        for(j = i + 1; j < len;)
        {
			k = 0;
            if (gstr[j] == gstr[i]) {
			    idx_tmp = j;
				len_tmp = 1;
				k++;
				while (gstr[j + k] == gstr[i + k]) {
					len_tmp++;
					k++;
				}
				if (len_tmp > ret->len) {
				    ret->len = len_tmp;
					ret->idxo = i;
					ret->idx = idx_tmp;
				}
				j++; /* 忘记循环变量要进行驱动 */
			} else {
			    j++;
			}
	    }
    }

    return ret;
}

int main()
{
    struct result * ret = get_max_len_repeated_str_and_its_idx(gstr);
    if (ret == NULL)
    {
        printf("get max len repeated str failed \n");
        exit(-1);
    }
    printf("idx %d, len %d, idxo %d \n", ret->idx, ret->len, ret->idxo);
    
    int i = 0;
    printf("1 compared: ");
    for (i = 0; i < ret->len; i++)
    {
        printf("%c", gstr[ret->idxo + i]);
    } 
    printf("\n");

    printf("2 compared with: ");
    for (i = 0; i < ret->len; i++)
    {
        printf("%c", gstr[ret->idx + i]);
    }
    printf("\n");

    return 0;
}

