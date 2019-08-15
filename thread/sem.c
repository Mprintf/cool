//posix标准信号量的操作

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include <semaphore.h>
int ticket=100;
sem_t sem;
void* thr_start(void* arg){
  while(1){
    //阻塞等待
    //int sem_wait(sem_t *sem);
    //非阻塞等待
    //int sem_trywait(sem_t *sem);
    //限时等待
    //int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout)
    sem_wait(&sem);
    if(ticket>0){
      printf("get a ticket:%d\n",ticket);
      ticket--;
    }else{
      sem_post(&sem);
      pthread_exit(NULL);
    }
    //int sem_post(sem_t *sem);计数+1，促使其他线程操作满足，然后唤醒其他线程
    sem_post(&sem);
  }
  return NULL;
}
int main(){
  int i,ret;
  pthread_t tid[4];
  sem_init(&sem,0,1);
  for(i=0;i<4;i++){
    ret=pthread_create(&tid[i],NULL,thr_start,NULL);
    if(ret!=0){
      printf("pthread create error\n");
      return -1;
    }
  }
  for(int i=0;i<4;i++){
    pthread_join(tid[i],NULL);
  }
  sem_destroy(&sem);
  return 0;
}
