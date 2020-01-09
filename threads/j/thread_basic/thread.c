#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
//Thread function need to look like in a certain way 
// they need to take void* as an argument and return void pointer.

void* myturn(void* args){
	int i;
	for (i=0; i < 4; i++){
		sleep(2);
		printf ("My Turn!\n");
	}
}

void yourturn(){
	int i;
	for (int i =0 ; i < 4; i++){
		sleep(1);
		printf ("Your Turn!\n");
	}
}

int main (){

        pthread_t t1;    // pthread_create(&thread_var, NULL, thread_func, NULL)
	pthread_create(&t1, NULL, myturn, NULL);
	yourturn();
	pthread_join(t1, NULL);
}

	




