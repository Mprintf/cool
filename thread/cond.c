//条件变量的基本使用
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

int _have_noodle=0;
pthread_mutex_t mutex;
pthread_cond_t cond_eat;
pthread_cond_t cond_cook;
void *eat_noodle(void *arg){
  while(1){
    pthread_mutex_lock(&mutex);
    while(_have_noodle==0){
      //休眠之前先解锁
      //pthread_cond_wait实现了三步操作：解锁、休眠、被唤醒后加锁，解锁和休眠必须是原子操作
      pthread_cond_wait(&cond_eat,&mutex);
    }
    printf("eat noodle!\n");
    _have_noodle=0;
    pthread_cond_signal(&cond_cook);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void *cook_noodle(void *arg){
  while(1){
    pthread_mutex_lock(&mutex);
    while(_have_noodle==1){
      pthread_cond_wait(&cond_cook,&mutex);
    }
    printf("cook noodle!\n");
    _have_noodle=1;
    pthread_cond_signal(&cond_eat);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int main(){
  pthread_t tid1,tid2;
  pthread_mutex_init(&mutex,NULL);
  pthread_cond_init(&cond_eat,NULL);
  pthread_cond_init(&cond_cook,NULL);
  for(int i=0;i<4;i++){
    int ret=pthread_create(&tid1,NULL,eat_noodle,NULL);
    if(ret!=0){
      printf("pthread create error\n");
      return -1;
    }
  }
  for(int i=0;i<4;i++){
    int ret=pthread_create(&tid2,NULL,cook_noodle,NULL);
    if(ret!=0){
      printf("pthread create error\n");
      return -1;
    }
  }
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond_eat);
  pthread_cond_destroy(&cond_cook);
  return 0;
}
