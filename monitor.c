#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/types.h>  
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>



//要监控的程序
#define P2 "vslamdemo_shm_1109"
#define P1 "main_slam"
#define UPDATE_PATH "/tmp/"
#define PATH "./"

/*****************************/
int is_run(char *name);
void killall_process(void);
/*****************************/


//运行返回1，没有运行返回0
int is_run(char *name)
{
    int ret = -1;
    char buf[256] = {'\0'};
    snprintf(buf, sizeof(buf), "pidof %s >> /dev/null", name); 
    ret = system(buf);

    if(!WEXITSTATUS(ret)){ //#include <sys/wait.h>
        printf("%s is running!\n", name);
        return 1;
    }
    else{
        printf("%s is not running!\n", name);
        return 0;
    }
}

void killall_process(void)
{ 
    char buf[128] = {'\0'};
    snprintf(buf, sizeof(buf), "killall -9 %s", P1);
    system(buf);
    snprintf(buf, sizeof(buf), "killall -9 %s", P2);
    system(buf);

}

void move_process(const char * process_name)
{
    char buf[128] = {'\0'};
    snprintf(buf, sizeof(buf), "mv /tmp/soc_upgrade.ota ./%s", process_name);
    system(buf);
}

void kill_process(const char * process_name)
{
    char buf[128] = {'\0'};
    snprintf(buf, sizeof(buf), "killall -9 %s", process_name);
    system(buf);
}

void start_process(const char * process_name)
{
    char buf[128] = {'\0'};
    snprintf(buf, sizeof(buf), "%s/%s > /dev/null 2>&1 &", PATH, process_name);
    system(buf);
}

int main(int argc, char **argv)
{
    int p1_ret = -1;
    int p2_ret = -1;
    int pipe_cmd = 0;
    char buf[128];
    bzero(buf, sizeof(buf));
    mkfifo("my.p",0664);
 /*   FILE * fp;
    fp = fopen("test.txt","r+");
    if( flock(fileno(fp),LOCK_EX) != -1 )
    {
        // 成功加独占锁！
        printf("\n成功加独占锁\n");
    }*/
    //1.判断2个主程序是否存在

    //判断主程序备份是否存在，不存在备份主程序

    while(1){

        p1_ret = is_run(P1);
        p2_ret = is_run(P2);

        if (!(p1_ret && p2_ret))
        {
            //killall_process();
            //打印日志信息
            //system("date >> w.log");
        }
        if(!p1_ret){
            start_process(P1);
            printf("\nP1 %s/%s &", PATH, P1);
        }
        if(!p2_ret){
            start_process(P2);
            printf("\nP2=%s/%s &", PATH, P2);
        }
        fflush(stdout);
        //获取管道信息 1,升级； 2,wifi重新配网 3,kill bot3
        //
        switch (pipe_cmd)
        {
            case 1:
                printf("\n 1,升级download finished !\n");
                kill_process(P1);
                //等待彻底结束
                move_process(P1);
                break;
            case 2:
                printf("\n 2,配网按钮按下：wifi重新配网!\n");
                kill_process(P1);
                break;
            case 3:
                printf("\n 3,kill bot3,进入省电模式!\n");
                kill_process(P2);
                break;
            case 4:
                printf("\n 4,唤醒 bot3,进入待机模式!\n");
                kill_process(P1);
                break;
            default:break;
        }
        sleep(5);
    
    }
    exit(0);
}
