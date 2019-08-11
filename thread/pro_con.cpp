//生产者与消费者模型

#include<iostream>
#include<queue>
#include<pthread.h>
#define MAX_QUEUE 10

class BlockQueue{
  private:
    std::queue<int> _queue;
    int _capacity;
    pthread_mutex_t _mutex;
    pthread_cond_t _cond_pro;
    pthread_cond_t _cond_con;
  public:
    BlockQueue(int cap=MAX_QUEUE):_capacity(cap){
      pthread_mutex_init(&_mutex,NULL);
      pthread_cond_init(&_cond_pro,NULL);
      pthread_cond_init(&_cond_con,NULL);
    }
    ~BlockQueue(){
      pthread_mutex_destroy(&_mutex);
      pthread_cond_destroy(&_cond_pro);
      pthread_cond_destroy(&_cond_con);
    }
    //生产者入队
    bool QueuePush(int data){
      pthread_mutex_lock(&_mutex);
      while(_queue.size()==_capacity){
        pthread_cond_wait(&_cond_pro,&_mutex);
      }
      _queue.push(data);
      //唤醒消费者
      pthread_cond_signal(&_cond_con);
      pthread_mutex_unlock(&_mutex);
    }
    //消费者进行出队
    bool QueuePop(int &data){
      pthread_mutex_lock(&_mutex);
      while(_queue.empty()){
        pthread_cond_wait(&_cond_con,&_mutex);
      }
      //获取队头数据
      data=_queue.front();
      _queue.pop();
      pthread_cond_signal(&_cond_pro);
      pthread_mutex_unlock(&_mutex);
    }
};
void *thr_consumer(void *arg){
  BlockQueue *q=(BlockQueue*)arg;
  while(1){
    int data;
    q->QueuePop(data);
    std::cout<<"consumer"<<pthread_self()<<"get data:"<<data<<std::endl;
  }
  return NULL;
}
void *thr_product(void *arg){
  BlockQueue *q=(BlockQueue*)arg;
  int i=0;
  while(1){
    q->QueuePush(i++);
    std::cout<<"product:"<<pthread_self()<<"push data:"<<i<<std::endl;
  }
  return NULL;
}
int main(){
  pthread_t con_tid[4],pro_tid[4];
  BlockQueue q;
  for(int i=0;i<4;i++){
    int ret=pthread_create(&con_tid[i],NULL,thr_consumer,(void*)&q);
    if(ret!=0){
      std::cout<<"pthread create error\n";
      return -1;
    }
  }
  for(int i=0;i<4;i++){
    int ret=pthread_create(&pro_tid[i],NULL,thr_product,(void*)&q);
    if(ret!=0){
      std::cout<<"pthread create error\n";
      return -1;
    }
  }
  for(int i=0;i<4;i++){
    pthread_join(con_tid[i],NULL);
  }
  for(int i=0;i<4;i++){
    pthread_join(pro_tid[i],NULL);
  }
  return 0;
}


