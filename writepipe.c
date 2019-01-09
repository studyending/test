#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    mkfifo("my.p",0664);
    int outfd = open("my.p",O_WRONLY);
    if(outfd==-1)
        perror("open my.txt"),exit(1);
    char buf[1024]={};
    int n = 0;
    while(fgets(buf,1024,stdin))
    {   
        write(outfd,buf,1024);
        memset(buf,0x00,1024);
    }  
    close(outfd);
return 1;
}
