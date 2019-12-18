#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>   /* basic socket definition */
#include<sys/types.h>
#include<signal.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>  /* for inet_pton and the like */
#include<stdarg.h>   /* for variable argument function , like err_n_die */
#include<errno.h>
#include<fcntl.h>
#include<sys/time.h>
#include<sys/ioctl.h>
#include<netdb.h>
#include <stdarg.h>
#include <limits.h>
#include<pthread.h>
#include"myqueue.h"

#define SERVERPORT 8989
#define BUFSIZE 4096
#define SOCKETERROR (-1)
#define SERVER_BACKLOG 1
#define THREAD_POOL_SIZE 20

pthread_t thread_pool[THREAD_POOL_SIZE];

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

void * thread_function(void *args);

void* handle_connection(void* p_client_socket);
int check(int exp, const char* msg);

int main(int argc, char **argv){

    int server_socket, client_socket, addr_size;
    SA_IN server_addr, client_addr;

    for (int i=0; i < THREAD_POOL_SIZE; i++){
	    pthread_create(&thread_pool[i], NULL, thread_function, NULL);
    }

    check ((server_socket = socket(AF_INET, SOCK_STREAM, 0)),"Failed to create socket");
    
    // Initialize the struct 
    server_addr.sin_family = AF_INET ;
    server_addr.sin_addr.s_addr =   INADDR_ANY;
    server_addr.sin_port = htons(SERVERPORT);

    check(bind(server_socket, (SA*)&server_addr,sizeof(server_addr)),"bind failed !");

    check(listen(server_socket, SERVER_BACKLOG),"Listen Failed !");

    while (1) {
        printf("waiting for connctions ...\n");
        // wait for and eventually accept an incoming connection.
        addr_size = sizeof(SA_IN);
        check(client_socket= accept(server_socket, (SA*)&client_addr, (socklen_t*)&addr_size),"Accept Failed !");

        printf("Connected!\n");
        // do whatever we do with connections.
        //handle_connection(client_socket);
	// the below code is without thread pool
	/*
	int *p_client_socket = malloc (sizeof(int));
	*p_client_socket = client_socket;
	pthread_t t1;
	pthread_create(&t1, NULL, handle_connection, p_client_socket);
*/

       int *p_client_socket = malloc(sizeof(int));
       *p_client_socket = client_socket;
       enqueue(p_client_socket);
    }// while
    return 0;

}

int check(int exp, const char* msg){

    if (exp == SOCKETERROR){
        perror(msg);

    }
    return exp;
}

void* handle_connection(void* p_client_socket){
    char buffer[BUFSIZE];
    size_t bytes_read;
    int msgsize = 0;
    char actualpath[PATH_MAX + 1];

    int client_socket = *((int*)p_client_socket);


    // read the client message ---- the name of the file to read 

    while ((bytes_read = read(client_socket, buffer+msgsize, sizeof(buffer)-msgsize-1)) > 0){
        msgsize += bytes_read;
        if (msgsize > BUFSIZE-1 || buffer[msgsize -1] == '\n') break;
        
    check(bytes_read, "recv_error");
    }
    buffer[msgsize-1] = 0;  // null terminate the message and remove the '\n'

    printf ("REQUEST: %s\n", buffer);
    fflush(stdout);

    // validity check
    if (realpath(buffer, actualpath) == NULL){
        printf ("ERROR(bad path): %s\n", buffer);
        close(client_socket);
        return NULL;
    }

    // read file and send its content to client

    FILE *fp = fopen(actualpath, "r");
    if(fp == NULL){
        printf("ERROR(open):%s\n", buffer);
        close(client_socket);
        return NULL;

    }

    // read file content and send them to client 
    //this is a fine example programm but rather insecure 
    // a real programm would limit the client to certain files.

    while((bytes_read= fread(buffer, 1, BUFSIZE,fp)) > 0){
        printf ("Sending %zu bytes\n", bytes_read);
        write(client_socket, buffer, bytes_read);
        close(client_socket);
        fclose(fp);
        printf("closing connection\n");
	return NULL;
    }
}


void* thread_function(void* args){


	while(true){
		int *pclient = dequeue();
		if (pclient != NULL){
			//we have a connection to work
			handle_connection(pclient);
		}
	}
}

