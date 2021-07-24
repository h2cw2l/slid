#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>

#define PORT 10234
#define SERVER "192.168.211.166"
#define LISTEN_Q 5
#define BUF_SIZE 4096
#define MAX_EVENTS 500

struct client{
    int fd;
    struct client * next;
};

struct client * head = NULL;
struct client * tail = NULL;

void delete_ele_from_client_list(void * head_local, int fd){

    struct client * tmp = (struct client *)head_local;
    if(fd == tmp->fd){
        head = tmp->next;
        free(tmp);
        return;
    }

    struct client * prev = tmp;
    tmp = tmp->next;
    while(tmp){
        if(fd == tmp->fd){
            prev->next = tmp->next;
            free(tmp);
            return;
        }
        
        prev = tmp;
        tmp  = tmp->next;
    }

    printf("\ndelete fs %d failed, does not exists int link list\n", fd);
    return;
}

int setup_listen_sock() 
{
    int sockfd, len;
    struct sockaddr_in address;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1) {
        perror("socket");
        exit(1);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(SERVER);
    address.sin_port = htons(PORT);
    len = sizeof(address);
    
    int on = 1;
    if(setsockopt(sockfd,SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1){
        perror("setsockopt");
        exit(-1);
    }

    if(bind(sockfd, (struct sockaddr *)&address, len) == -1) {
        perror("bind");
        exit(1);
    }

    if(listen(sockfd, LISTEN_Q) == -1) {
        perror("listen");
        exit(1);
    }

    return sockfd;    
}

int main()
{
    int listen_sockfd;
    int i = 0;
    int ret = 0;
    int client_len;
    struct sockaddr_in client_address;    
    char rwbuf[BUF_SIZE] = {0};
    
    listen_sockfd = setup_listen_sock();
    struct epoll_event eventArray[MAX_EVENTS];
    struct epoll_event event_listend;
    struct epoll_event event_stdin;
    int epollfd = epoll_create(MAX_EVENTS);
        
    event_listend.events = EPOLLIN;
    event_listend.data.fd = listen_sockfd;
    
    event_stdin.events = EPOLLIN;
    event_stdin.data.fd = STDIN_FILENO;
    
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sockfd, &event_listend) < 0 )
    {
        printf("epoll 加入失败 fd:%d\n", listen_sockfd);
        exit(-1);
    }
    
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, STDIN_FILENO, &event_stdin) < 0)
    {
        printf("epoll 加入失败 fd:%d\n", listen_sockfd);
        exit(-1);
    }

    while(1) 
    {
        printf("server waiting\n");        
        sleep(1);
        printf("after sleep\n");	
        ret = epoll_wait(epollfd, eventArray, MAX_EVENTS, -1);

        if(ret < 0)
        {
            perror("epoll_wait");
            exit(1);
        }
        
        for(i = 0; i < ret; i++) 
        {            
            if((eventArray[i].events & EPOLLERR) ||
               (eventArray[i].events & EPOLLHUP) || 
               !(eventArray[i].events & EPOLLIN)) 
            {
                perror("epoll error");
                close(eventArray[i].data.fd);
                delete_ele_from_client_list((void *)head, eventArray[i].data.fd);
                exit(-1);
            }
            else if(eventArray[i].data.fd == listen_sockfd)
            {  
                struct client * tmp = NULL;
                tmp = (struct client *)malloc(sizeof(struct client));
                if(NULL == tmp){
                    printf("\nmalloc for tmp failed\n");
                    exit(-1);
                }
                tmp->fd = 0;
                tmp->next = NULL;
                
                if(NULL == head){
                    head = tmp;
                    tail = tmp;
                }
                
                client_len = sizeof(client_address);
                tmp->fd = accept(listen_sockfd, (struct sockaddr *)&client_address, &client_len);

                tail->next = tmp;
                
                struct epoll_event event_cli;
                event_cli.data.fd = tmp->fd;
                event_cli.events = EPOLLIN;
                epoll_ctl(epollfd, EPOLL_CTL_ADD, tmp->fd, &event_cli);
                printf("adding client on fd %d\n", tmp->fd);
            }
            else if(STDIN_FILENO == eventArray[i].data.fd)
            {
                read(STDIN_FILENO, rwbuf, BUF_SIZE);  
                struct client * tmp1 = head;

                //while(tmp1 != NULL){
                    send(tmp1->fd, rwbuf, strlen(rwbuf), 0);
                    //printf("send client fd %d: %s\n",tmp1->fd, rwbuf);
                    //tmp1 = tmp1->next;
                //}
            }
            else
            {
                int nread = 1;
                ioctl(eventArray[i].data.fd, FIONREAD, &nread); 
                if(nread == 0) 
                {  
                    close(eventArray[i].data.fd);
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, eventArray[i].data.fd, &eventArray[i]);
                    delete_ele_from_client_list((void *)head, eventArray[i].data.fd);
                    printf("removing client on fd ：%d\n", eventArray[i].data.fd);
                }
                else
                {
                    read(eventArray[i].data.fd, rwbuf, BUF_SIZE);
                    printf("recv fd %d: %s\n", eventArray[i].data.fd, rwbuf);
                }
            }
        }
    }
    
    close(epollfd);
}

