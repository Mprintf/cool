//体验每一个线程都是一个执行流
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void* thr_entry(void* arg){
  while(1){
    printf("i am commom thread---%s\n",(char*) arg);
    sleep(1);
  }
  return NULL;
}

int main(){
  pthread_t tid;
  char *param="this is input param";
  int ret=pthread_create(&tid,NULL,thr_entry,(void*)param);
  if(ret!=0){
    printf("pthread create error\n");
    return -1;
  }
  printf("tid:%p\n",tid);
  while(1){
    printf("i am main thread---\n");
    sleep(1);
  }
  return 0;
}
