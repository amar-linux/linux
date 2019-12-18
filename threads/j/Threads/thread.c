#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

// The function that is taken as an argument for pthread_create has to look certain way
// they have to take void* as argument and returs void *

void* myturn(void* arg){
  int i;


  for (i=0; i<8; i++){
  sleep(1);
  printf("My turn !--%d\n",i);
}
//pthread_exit(NULL);

printf("End myturn\n");
return a;
}

void yourturn(){

int i;
  for (i=0; i<7;i++){
   sleep(2);
  printf("Your Turn !--%d\n",i);
   }
  return NULL;
}

int main(){

  pthread_t newthread;
// thread_create thread_function
// pthread_create(&newthread, NULL, thread_function_name ), and should fit the bill.
  pthread_create(&newthread, NULL, myturn,NULL);
  
  pthread_join(&newthread, a);
  //myturn();
  yourturn();
  printf("Thread Complete\n");

}


// gcc compilation for the programm that has pthread functions is -pthread
//gcc -pthread thread.c
