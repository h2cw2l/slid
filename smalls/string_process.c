#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>


char request[256] = {'\0'};
void main()
{
    char *pSeg = "||";
    char *pCmdSeg = NULL;
    char *pCmd = "n0||0||0||0||0||#000000||0||0||0.0||0||0||0||0||0||0||0||0||0||0||0||1||0||0||0||0||0";
    int i;

    pCmdSeg = strstr(pCmd, pSeg) + 2;
    for (i = 0; i < 19; i++) {
        pCmdSeg = strstr(pCmdSeg, pSeg) + 2;
    }
    printf("%c\n", *pCmdSeg);
    
    strcpy(request, pCmd);
    printf("request %s\n", request);

    return;
}
