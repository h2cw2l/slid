#include <stdio.h>
 
int main()
{
    char strbuf[12];
    FILE* fp;
    fp = fopen("./temp","r");
    fread(strbuf,sizeof(char),11,fp);
    printf("read content is %s \n", strbuf);
    
    return 0;
}
