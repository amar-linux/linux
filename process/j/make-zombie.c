#include<stdio.h>
#include<unistd.h>

int main(){
while(1){
	if (fork() == 0){
		printf ("child started and done! (%d)\n",getpid());
		return 0;
	}else{
		printf("Parent just wont die...\n");
		sleep(20);
	}
}
}
