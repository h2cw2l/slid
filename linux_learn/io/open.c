#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
    int fd;
    fd = open("/proc/41253/21", O_RDONLY);
    printf("fd %d \n", fd);

    return 0;
}
