#include<stdio.h>
#include<pthread.h>
#include<stdint.h>

#define BIG 10000000
int counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void* count_to_big(void* args){

        int i;
	for (i=0; i < BIG; i++){
		pthread_mutex_lock(&mutex);
		counter ++;
		pthread_mutex_unlock(&mutex);
	}
	return  NULL; 
}

pthread_t t1;
int main(){
	pthread_create(&t1,NULL, count_to_big,NULL);
	count_to_big(NULL);
	//count_to_big();
	pthread_join(t1,NULL);
	printf ("Done, Counter = %u\n",counter);
}
