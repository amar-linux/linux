#include<stdio.h>
#include<unistd.h>



int main(){


        int value;
	if ((value =fork()) == 0){
		printf("I am childish and pid is %d,%d\n",getpid(),value);
		execlp("ls","ls","-al",NULL);
	}else{
		printf ("I am old Parental. %d\n",getpid());
	}
}
	  
