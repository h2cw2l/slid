#include "stdlib.h"
#include "stdio.h"
#include "string.h"


char *str = "abcdafffmmmlmnabcdabcdafffmmm";


/* 课本上的查找的是正确的，自己找的反而不太对啊 */
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
				j += len1;
			} else {
			    j++;
			}

			// tmpj++;
			// j = tmpj;
		}

		i++;
	}
    
	printf("maxi = %d, maxii = %d, maxlen %d\n", maxi, maxii, maxlen);
	for (i = maxi; i < maxi + maxlen - 1; i++) {
	    printf("%c", str[i]);
	}
	printf("\n");
    

	return 0;
}
