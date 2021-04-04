#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

void * get_shm_addr()
{
    key_t key = ftok("/home/wyl/self/selfcode/fd_share/bpf_shm", 1);
    if (key < 0)
    {
        printf("ftok failed\n");
        return;
    }
    printf("key %d\n", key);

    int id = shmget(key, 2048, IPC_CREAT | 0777);
    if (id < 0)
    {
        printf("shmget failed\n");
        return;
    }
    printf("id %d\n", id);

    char * shmaddr = shmat(id, NULL, 0);
    printf("addr %p \n", shmaddr);
    
    //*shmaddr = 123;
    //printf("after fuzhi \n");
    //char * addr1 = shmat(id, shmaddr, SHM_RND);
    printf("value %d \n", *shmaddr);

    return shmaddr;
}


int main()
{
    int i = 0;
    for (i = 0; i < 100; i++)
    {
        get_shm_addr();
	sleep(1);
    }

    pid_t pid = fork();
    if (0 == pid)
    {
        get_shm_addr();
    }

    return 0;
}
