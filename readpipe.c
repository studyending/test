#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int file_exists(char * filename)
{
    return (access(filename,0)==0);
}

int main()
{
    int infd = open("my.p",O_RDONLY);
    if(infd==-1)
        perror("open my.p"),exit(1);
    char buf[1024]={};
    int n = 0;
    while((n = read(infd,buf,1024))>0)
    {
        write(1,buf,n);
        //printf("\n buf0=%d \n",buf[0]);
        switch (buf[0])
        {
            case '1':
                printf("\n receive pipe 1 \n");
                break;
            case '2':
                printf("\n receive pipe 2 \n");
                break;
            case '3':
                printf("\n receive pipe 3 \n");
                break;
            default:
                break;
        }
        memset(buf,0x00,1024);
    }
    close(infd);                                                                                                         
    unlink("my.p"); //删除管道
    return 0;
}
