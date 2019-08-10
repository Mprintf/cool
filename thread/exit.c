//体验每一个线程退出的集中方式
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void* thr_entry(void* arg){
  sleep(5);
  //线程终止
  //pthread_cancel((pthread_t)arg);
  pthread_exit("hello");
  while(1){
    printf("i am commom thread---%s\n",(char*) arg);
    sleep(1);
  }
  return NULL;
}

int main(){
  pthread_t mtid;
  //获取自身线程ID
  mtid= pthread_self();
  pthread_t tid;
  char *param="this is input param";
  //线程创建
  int ret=pthread_create(&tid,NULL,thr_entry,(void*)mtid);
  if(ret!=0){
    printf("pthread create error\n");
    return -1;
  }
  //线程等待
  void *retval;
  pthread_join(tid,&retval);
  printf("tid:%p retval:%s\n",tid,retval);
  //取消线程
  //pthread_cancel(tid);
  while(1){
    printf("i am main thread---\n");
    sleep(1);
  }
  return 0;
}
