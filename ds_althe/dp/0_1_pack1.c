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

unsigned int process[21][/* 20 */ 200] = {0};

unsigned int gift_select_status[20] = {0};
unsigned int gift_select_result[20] = {0};

unsigned int vol = 0;
unsigned int val = 0;

void zero_one_pack()
{
    unsigned int vol_tmp = 0;
    unsigned int val_tmp = 0;
    int i = 0;
    int j = 0;

    for (i = 0; i < 20; i++)
    {
        if (gift_vol[i] <= PACK_VOLUME)
	{
	    // 二维数组就要跟上一行进行对比
	    for (j = PACK_VOLUME; j >= gift_vol[i]; j--)
            {
	        if (process[i /*+ 1*/][j - gift_vol[i]] + gift_val[i] > process[i][j])
	        {
		    process[i + 1][j] = process[i][j - gift_vol[i]] + gift_val[i];
		}
		else // else分支也是必须的
	        {
		    process[i + 1][j] = process[i][j];
		}
	    }
            
	    // 这个循环一开始忘了
	    for (j = gift_vol[i] - 1; j >= 0; j--)
            {
                process[i + 1][j] = process[i][j];
            }

	}	
    }

    return;
}

int main()
{
    int i = 0;
    zero_one_pack();
    for (i = 0; i < 200; i++)
    {
        printf("i %u, val %u \n", i, process[20][i]);
    }
    return 0;
}


