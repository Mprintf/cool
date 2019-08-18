/*=============================================================== 
*   Copyright (C) . All rights reserved.")
*   文件名称： 
*   创 建 者：zhang
*   创建日期：
*   描    述：进程创建 
*       pid_t fork(void);
*       通过复制调用进程，创建一个新的子进程
================================================================*/
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();
    if (pid < 0) {
        printf("fork error\n");
        return -1;
    }else if (pid == 0) {
        printf("i am child:%d\n",getpid());
    }else {
        printf("i am parent:%d\n",getpid());
    }
    while(1){
      printf("2333\n");
      sleep(1);
    }
    return 0;
}
