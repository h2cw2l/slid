#include "stdlib.h"
#include "stdio.h"
#include "string.h"

// 51
char *gstr = "aaaaaaaaaaaaaaaaaaaafaswerptowakfafoiwdwerpabcwerptoasldfkfafoiwdwerpabcdfadlkfaabcaaaaaaaaaaaaaaaaaaaa";
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
    
    // 临界点，特殊情况时必须要考虑到的
    // simple
    for (i = 0; i < len - 1 /* len */; i++)
    {
	idx_tmp = 0;
	len_tmp = 0;
	k = 0;
        for(j = i + 1; j < len; j++)
        {
	    if (str[j] == str[i + k])
            {
	        if (k == 0)
	        {
		    idx_tmp = j; // j时会回退的，因为每一次对i的循环，j都会回退一次
		}

		len_tmp++;
		k++;
	    }
	    else
            {
                if (len_tmp > ret->len)
		{
		    ret->len = len_tmp;
		    ret->idx = idx_tmp;
		    ret->idxo = i;
		    printf("replace len %d, idx %d, k %d, i %d \n", ret->len, ret->idx, k, i);
		}

		idx_tmp = 0;
		len_tmp = 0;
		k = 0;
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
    printf("1: ");
    for (i = 0; i < ret->len; i++)
    {
        printf("%c", gstr[ret->idxo + i]);
    } 
    printf("\n");

    printf("2: ");
    for (i = 0; i < ret->len; i++)
    {
        printf("%c", gstr[ret->idx + i]);
    }
    printf("\n");

    return 0;
}

