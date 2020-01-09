#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>


//pass arguments to the thread and returns from threads 

// thread function takes void* and returns void * meaning 
// we can pass anything and take anything as a return.

void* myturn(void *args){

	int i;
	int *rptr =(int*)args;
	int *iptr = (int*) malloc(sizeof(int));
	*iptr =5;
	for (i =0; i<4; i++){
		sleep(1);
		printf ("Myturn! %d, vall-arg=%d\n",i,i*(*rptr));
		(*iptr)++;
	}
 return iptr;
}

void yourturn(){
	int i;
	for (i =0; i < 4; i++){
		sleep(2);
		printf ("Your Turn! %d\n",i);
	}
}

int main(){

	pthread_t t1;
	void *result;
//	void *vptr ;
	int rptr =5;
  //      vptr = &ptr;
  // an adress is just an address and can be taken as a void pointer too.
	pthread_create(&t1, NULL, myturn,&rptr);
	yourturn();
	pthread_join(t1,&result);
	printf ("Thread function completed vlue returned, result =%d\n",*((int*)result));
}
