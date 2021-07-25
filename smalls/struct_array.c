#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INNERR "hello","chnia"
struct Student
{
    char *name;
	char *hometown;
    int score;
	char *gender;
};

struct Student S1[3]={{INNERR, 0,"male"},{INNERR, 2,"male"},{INNERR, 3, "male"}};

int main()
{
	printf("0 name %s, ht %s, score %d, gender %s\n", S1[0].name, S1[0].hometown, S1[0].score, S1[0].gender);
	char str[10] = "hello";
	printf("str %s\n", str);
	
	return 0;
}

