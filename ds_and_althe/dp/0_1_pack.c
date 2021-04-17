#include "stdlib.h"
#include "stdio.h"
#include "string.h"


#define PACK_VOLUME 200
unsigned int gift_vol[20] = 
{10, 5,  6,  8, 19, 20, 18, 25, 77, 11,
 17, 18, 50, 3, 9,  33, 61, 22, 10, 13};

unsigned int gift_val[20] =
{100, 200, 150, 110, 180, 66, 77, 88, 99, 96,
 111, 222, 198, 32,  11,  22, 56, 57, 11, 12};

unsigned int gift_select_status[20] = {0};
unsigned int gift_select_result[20] = {0};

unsigned int vol = 0;
unsigned int val = 0;

void zero_one_pack(int idx)
{
    unsigned int vol_tmp = 0;
    unsigned int val_tmp = 0;
    int i = 0;

    if (idx == 20)
    {
        for (i = 0; i < 20; i++)
	{
	    // 这个结果不一定要保存下来，需要保存下来的时候再把状态更新进去才可以
	    // gift_select_result[i] = gift_select_status[i];
	    if (gift_select_status[i] == 1)
            {
	        vol_tmp += gift_vol[i];
		val_tmp += gift_val[i];
	    }
	}
        
        if ((vol_tmp <= PACK_VOLUME) && (val_tmp > val))
	{
	    vol = vol_tmp;
	    val = val_tmp;

	    for (i = 0; i < 20; i++)
            {
	        gift_select_result[i] = gift_select_status[i];
	    }
	}	
    }

    // 递归退出条件
    if (idx == 20)
    {
        return;
    }
    
    // 递归体
    gift_select_status[idx] = 0;
    zero_one_pack(idx + 1);

    gift_select_status[idx] = 1;
    zero_one_pack(idx + 1);

    return;
}

int main()
{
    int i = 0;
    zero_one_pack(0);
    printf("vol %u, val %u \n", vol, val);
    for (i = 0; i < 20; i++)
    {
        printf("i %d, select %u \n", i, gift_select_result[i]);
    }
    return 0;
}


