#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>



void* myturn(void* args){

    int i;

    for(i=0; i< 5; i++){
        sleep(1);
        printf ("My turn --%d\n",i);
    }
    return NULL;
}

void yourturn(){

    int i;

    for (i-0; i<6;i++){
        sleep(2);
        printf ("Your turn --%d\n",i);
    }
    return NULL;
}

int main(){

    pthread_t newthread;
    pthread_create(&newthread, NULL, myturn, NULL);
    yourturn();
    pthread_join(newthread, NULL);
    return NULL;
}
