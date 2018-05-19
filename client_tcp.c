/*************************************************************************
	> File Name: client_tcp.c
	> Author: 
	> Mail: 
	> Created Time: Sat 17 Mar 2018 16:38:26 CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#include<string.h>
#define PORT 6666
int main()
{
    char rmsg[60];char wmsg[60];
    int sockfd;char hostname[30]="localhost.localdomain";
    struct hostent *host=gethostbyname(hostname);
    struct sockaddr_in severaddr;
    if((sockfd=(socket(AF_INET,SOCK_STREAM,0)))<0)
    {
        printf("socket error.\n");
        return 0;
    }
    else{
        printf("socket success.\nsocket ID is %d\n",sockfd);
    }
    bzero(&severaddr,sizeof(struct sockaddr_in));
    severaddr.sin_family=AF_INET;
    severaddr.sin_port=htons(PORT);
    //printf("IP list is %s\n",(host->h_addr));
    severaddr.sin_addr=*((struct in_addr*)host->h_addr);//此处必须这样强制转换,其实char**h_addr_list是一个4字节的网络字节序的in_addr
    //severaddr.sin_addr.s_addr=inet_addr(&(host->h_addr));//只是用char*来表示，h_addr与struct in_addr形式是一样的。可以将host->h_addr强制转换为struct in_addr的指针
    if(connect(sockfd,(struct sockaddr*)&severaddr,sizeof(struct sockaddr))==-1)
    {
        printf("connecting error.\n");
        return;
    }
    else{
        printf("connecting successfully.\n");
    }
    while(1)
    {
	  /*bzero(rmsg,sizeof(rmsg));
    read(STDIN_FILENO,rmsg,sizeof(rmsg));
    if(send(sockfd,wmsg,sizeof(wmsg),0)<0)
      perror("ERROR");
    
    bzero(wmsg,sizeof(wmsg));
    recv(sockfd,rmsg,sizeof(rmsg),0);
    printf("[receive]:%s\n",rmsg);*/

        //memset(rmsg,0,sizeof(rmsg));
            if(read(sockfd,rmsg,sizeof(rmsg))<0)
            {
                printf("Reading error.\n");
                return 0;
            }
            else
            {
                printf("The message is:%s\n",rmsg);
		bzero(rmsg,sizeof(rsmg));
            }
            printf("Sending:");
            gets(wmsg);
            if(write(sockfd,wmsg,sizeof(wmsg))==-1)
            {
                printf("writting error.\n");
                return 0;
            }
            else
            {
                printf("Sending completely.\n");
                memset(wmsg,0,sizeof(wmsg));
            }  
    }
    close(sockfd);
    return 0;
}
