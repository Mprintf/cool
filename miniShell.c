#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<ctype.h>
#include<fcntl.h>

int main() {
  while(1){
    printf("[MXS@localhost]$");
    fflush(stdout);
    char tmp[1024]={0};
    scanf("%[^\n]%*c",tmp);

    char *ptr=tmp;
    int redirect_flag=0;
    char *redirect_file=NULL;
    while(*ptr!='\0'){
      if(*ptr=='>'){
        *ptr='\0';
        redirect_flag=1;
        ptr++;
        if(*ptr=='>'){
          *ptr='\0';
          redirect_flag=2;
          ptr++;
        }
        while(isspace(*ptr)&&*ptr!='\0')
          ptr++;
        redirect_file=ptr;
        while(!isspace(*ptr)&&*ptr!='\0')
          ptr++;
        *ptr='\0';
      }
      ptr++;
    }
    ptr=tmp;
    int argc=0;
    char *argv[32]={NULL};
    while(*ptr!='\0'){
      if(!isspace(*ptr)){
        argv[argc]=ptr;
        argc++;
        while(!isspace(*ptr)&&*ptr!='\0'){
          ptr++;
        }
        *ptr='\0';
        ptr++;
        continue;
      }
      ptr++;
    }
    argv[argc]=NULL;
    int pid=fork();
    if(pid==0){
      int fd=1;
      if(redirect_flag==1){
        fd=open(redirect_file,O_CREAT|O_WRONLY|O_TRUNC,0664);
      }else if(redirect_flag==2){
        fd=open(redirect_file,O_CREAT|O_WRONLY|O_APPEND,0664);
      }
      dup2(fd,1);
      execvp(argv[0],argv);
      exit(0);
    }
    wait(NULL);
  }
  return 0;
}
