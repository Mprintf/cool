//通过黄牛抢票这个例子来体验没有互斥锁的线程
#include<stdio.h>
#include<pthread.h>

pthread_mutex_t mutex;
int ticket=100;
void* yellow_bull(void *arg){
  while(1){
    //int pthread_mutex_lock(pthread_mutex_t *mutex);
    //阻塞加锁：若现在不能加锁则一直等待
    //int pthread_mutex_trylock(pthread_mutex_t *mutex);
    //非阻塞加锁:若现在不能加锁则立即报错返回
    pthread_mutex_lock(&mutex);
    if(ticket>0){
      usleep(1000);
      printf("bull %d get a ticket:%d\n",(int)arg,ticket);
      ticket--;
    }else{
      printf("no tickets,bull %d exit\n",(int)arg);
      //加锁之后，需要在任意有可能退出线程的地方进行解锁
      pthread_mutex_unlock(&mutex);
      pthread_exit(NULL);
    }
    //int pthread_mutex_unlock(pthread_mutex_t *mutex);
    pthread_mutex_unlock(&mutex);
  }
}
int main(){
  pthread_t tid[4];
  // int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr)
  // mutex 互斥锁变量
  // attr 初始化互斥锁属性，通常置NULL
  pthread_mutex_init(&mutex,NULL);
  for(int i=0;i<4;i++){
    int ret=pthread_create(&tid[i],NULL,yellow_bull,(void*)i);
    if(ret!=0){
      printf("thread create error\n");
      return -1;
    }
  }
  for(int i=0;i<4;i++){
    pthread_join(tid[i],NULL);
  }
  pthread_mutex_destroy(&mutex);
  return 0;
}
