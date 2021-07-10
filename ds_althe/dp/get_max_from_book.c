#include "stdlib.h"
#include "stdio.h"
#include "string.h"

// 29
char *str = "abcdafffmmmlmnabcdabcdafffmmm";

// 课本上的查找的是正确的，自己找的反而不太对啊
// 动态规划就是目标总是变，只看重眼前利益
// 认为眼前的结果就是最好的
// 三层循环，第一层是做为被比较的基础，
//           第二层是拿来做比较的字符串，
//           第三岑是找到重复的往后遍历
// 数据结构：没有特定的数据结构，但是又三层循环，每一层的起止位置都是不一样的，
//           要记录中间的结果，并且维护信息在每一次循环开始的时候需要重新复位
// 接口    ：就一个函数就可以完成
// 流程    ：三层循环
int main()
{
    int maxi = 0, maxii = 0, maxlen = 0, len1, i = 0, j, k, str_len = 0;
    str_len = strlen(str);
    printf("strlen(str) = %d\n", str_len);
    if (str_len == 0) {
        printf("str len is 0\n");
        return -1;
    }
    
    int tmpj = 0;
    while (i < str_len - 1) {
	j = i + 1;
	tmpj = j;
	while (j < str_len) {
	    if (str[i] == str[j]) {
                len1 = 1;
                for (k = 1; str[i + k] == str[j + k]; k++) {
                    len1++;
                }
	        if (len1 > maxlen) {
	            maxi = i;
                    maxii = j;
                    maxlen = len1;
                    printf("replace, maxi %d, maxlen %d\n", maxi, maxlen);
                }
                // j += len1;
                j++;
	    } else {
                j++;
	    }

	    // tmpj++;
	    // j = tmpj;
	}

	i++;
    }
    
    printf("maxi = %d, maxii = %d, maxlen %d\n", maxi, maxii, maxlen);
    for (i = maxi; i < maxi + maxlen; i++) {
        printf("%c", str[i]);
    }
    printf("\n");

    return 0;
}
