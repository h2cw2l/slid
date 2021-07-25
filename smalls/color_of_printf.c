
#include <stdio.h>
 
#   define COL(x)  "\033[;" #x "m"
#   define RED     COL(31)
#   define GREEN   COL(32)
#   define YELLOW  COL(33)
#   define BLUE    COL(34)
#   define MAGENTA COL(35)
#   define CYAN    COL(36)
#   define WHITE   COL(0)
#   define GRAY    "\033[0m"
 
main()
{
  printf("hello,world\n");
  printf(RED"hello,world\n"GRAY);
  printf(GREEN"hello,world, %s\n"GRAY, "1234");
}
