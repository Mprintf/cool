#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/stat.h>

int main(){
  char *fifo={"./test.fifo"};
  umask(0);
  int ret=mkfifo(fifo,0664);
  if(ret<0){
    if(errno!=EEXIST){
      perror("mkfifo error");
      return -1;
    }
  }
  int fd=open(fifo,O_RDONLY);
  if(fd<0){
    perror("open error");
    return -1;
  }
  printf("fifo:%sopen success!!\n",fifo);
  while(1){
    char buf[1024]={0};
    read(fd,buf,1023);
    printf("peer say:%s\n",buf);
  }
  close(fd);
  return 0;
}

