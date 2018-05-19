/*************************************************************************
	> File Name: server_tcp.c
	> Author: 
	> Mail: 
	> Created Time: Sat 17 Mar 2018 15:33:46 CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#define PORT 6666
#define IP "127.0.0.1"
char rmsg[256];
char wmsg[256];
int main()
{
    int sockfd,newsockfd;
    struct sockaddr_in addr;
    struct sockaddr_in addrclient;
    int addr_len=sizeof(struct sockaddr_in);
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        printf("socket is not successful.\n");
        return 0;
    }
    else{
        printf("socket success.\n");
        printf("socket ID is %d\n",sockfd);
    }
    bzero(&addr,sizeof(struct sockaddr_in));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(PORT);
    addr.sin_addr.s_addr=htonl(INADDR_ANY);//inet_addr(IP);
    //printf("Local address is:%u\n",htonl(INADDR_ANY));
    if(bind(sockfd,(struct sockaddr*)(&addr),sizeof(struct sockaddr))==-1)
    {
        printf("bind is not successful.\n");
        return 0;
    }
    else
        printf("bind success.\nLocal port is %d\n",PORT);
    if(listen(sockfd,6)==-1)
    {
        printf("listen is not successful.\n");
        return 0;
    }
    else
        printf("listening...\n");
    if((newsockfd=accept(sockfd,(struct sockaddr*)(&addr),&addr_len))==-1)
        {
            printf("accept is not successful.\n");
            return 0;
        }
        else
        {
            printf("connecting client is %s\n",inet_ntoa(addrclient.sin_addr));
        }
    while(1)
    {
        
        printf("Sending message is:");
        gets(wmsg);
        //int pid;
        /*if((pid=fork())<0)
        {
            printf("process error.\n");
        }*/
        //else if(pid==0)
        
        if(write(newsockfd,wmsg,sizeof(wmsg))<0)
        {
            printf("writting error.\n");
            return 0;
        }
        else
        {
            printf("Writting success.\n");
	    bzero(wmsg,sizeof(wmsg));
        }
        
        //else
        
        if(read(newsockfd,rmsg,sizeof(rmsg))<0)
        {
            printf("reading error.\n");
            /*close(sockfd);
            printf("close connect.\n");
            return 0;*/
        }
        else //(rmsg!='\0')
        {
            if(*rmsg=='\0')
            {
                printf("close connect.\n");
                close(sockfd);
                return 0;
            }
            printf("Reading content is:%s\n",rmsg);
        }
            /*else
            {
                continue;
            }*/       
        //close(newsockfd);
    }   
    return 0;
}
