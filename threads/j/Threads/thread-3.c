#include<stdio.h>
#include<stdlib.h>
#define BIG 100000000
#include<pthread.h>

int count =0;

// count ++ is the crritical section there is possibility when both the thread
// reads the same value and icrements and writes it down known as race condition.

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* count_to_big(void* arg){

    int i;
    for (i =0; i<BIG; i++){
//        pthread_mutex_lock(&lock);
        count++;       // thie is the critical section which needs to be protected and hence the lock.
  //      pthread_mutex_unlock(&lock);
    }
    return NULL;
}


int main(){

   // count_to_big();
    pthread_t t1;

    pthread_create(&t1,NULL, count_to_big,NULL);
   // printf ("First count gets completed\n");
    count_to_big(NULL);

    pthread_join(t1,NULL);
    printf ("The value of count is %d\n.",count);

    return 0;
}

    

