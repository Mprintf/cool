#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

int main() {
  //管道必须创建于创建子进程之前，子进程才能复制到管道的操作句柄
  int pipefd[2];
  int ret=pipe(pipefd);
  if(ret<0) {
    perror("pipe error");
    return -1;
  }
  int pid=fork();
  if(pid==0) {
    //child
    char buf[1024]={0};
    read(pipefd[0],buf,1023);
    printf("child read:%s\n",buf);
  }else if(pid>0) {
    //parent
    sleep(1);
    write(pipefd[1],"hello world",11);
  }
  return 0;
}


