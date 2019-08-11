#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<ctype.h>


int main() {
  while(1) {
    printf("[MXS@localhost]$");
    fflush(stdout);
    char tmp[1024]={0};
    //获取一个连续的字符串%[^\n],从标准输入缓冲区取数据直到遇到\n截止，
    //%*c:将缓冲区中剩下的\n取出来；否则会造成死循环
    scanf("%[^\n]%*c",tmp);

    char *ptr=tmp;
    int argc=0;
    char *argv[32]={NULL};
    while(*ptr != '\0') {
      if(!isspace(*ptr)) {
        argv[argc]=ptr;
        argc++;
        while(!isspace(*ptr) && *ptr != '\0')
          ptr++;
        *ptr='\0';
        ptr++;
        continue;
      }
      ptr++;
    }
    argv[argc]=NULL;
    
    if(!strcmp(argv[0],"cd")){
      //改变当前工作路径
      chdir(argv[1]);
      continue;
    }

    int pid=fork();
    if(pid==0) {
      execvp(argv[0],argv);
      //若子进程替换程序失败，则直接退出，因为不需要多个shell
      exit(0);
    }
    wait(NULL);
  }
  return 0;
}
