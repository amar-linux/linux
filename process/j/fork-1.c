#include<stdio.h>
#include<unistd.h>
int main(){

        int value;
	if ((value= fork()) ==0){
		printf("I am child\n");
	}else{
		printf ("I am the parent and the child pid is %d and the value of getpid is:-%d\n",value,getpid());
	}
}
