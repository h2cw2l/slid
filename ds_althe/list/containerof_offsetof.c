#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct student{
    char name[15];
    unsigned char age;
    char hometown[16];
    char sex[2];
    unsigned char class;
} Student;

// 定义宏的时候，如果是多行的话，每一行都必须要用斜线连接起来，连成一行
// 宏定义是字符串替换，宏结束的时候是没有分号的
// do {...} while (0) 在宏定义中是什么意思 ？？？？能够确保引用宏的地方都能正确执行
// 主要是分号的使用，分号使用不当 和 if 语句的结合，这样就会改变原来的语义
// https://www.cnblogs.com/lanxuezaipiao/p/3535626.html 
// 宏定义的返回值是什么 ？？？？？
#define offset_of(type, member) \
(&(((type *)(void *)0)->member))

//#define container_of(ptr, type, member) \
//(type *)(void *)((unsigned long)ptr - (unsigned long)(((type *)(void *)0)->member));
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
// 这里用字符串代替的话，怎么能赋值呢，并且中间有一个表达式了
// 在这个表达式后边，怎么还能赋值呢
#define container_of(ptr, type, member) ({                      \
        typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})


int main()
{
    Student *stu = (Student *)malloc(sizeof(Student));
    if (stu == NULL) {
        printf("malloc for stu failed\n");
        exit(0);
    }    
    
    printf("stu %p, sex %p, &sex %p, sex + 1 %p, &sex + 1 %p\n",
           stu, stu->sex, &(stu->sex), stu->sex + 1, &(stu->sex) + 1);
    // 对于一个数组来说，数组名是地址，给这个数组名取地址之后
    // 仍然是一个地址，只不过对这两个地址做加法运算时候
    // + 1 的步幅是不一样的
    // 去掉小括号和最后一行表达式已经赋值给其它变量，就不对了
    Student *ctn = container_of(&(stu->sex), Student, sex);
    printf("container %p\n", ctn);
    
    int offset_of_age = offset_of(Student, age);
    printf("offesetof age %d\n", offset_of_age);
    
    // void value not ignored as it ought to be 没有返回值，但是又把这个返回值赋值了
    // 这相当于是一个函数了, 外边加一层小括号，相当于一个函数
    int a = ({int b = 6; 6 + 6;});
    printf("a %d\n", a);
    return 0;
}
