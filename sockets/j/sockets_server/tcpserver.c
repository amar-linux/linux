#include"common.h"
#include<string.h>

int main(int argc, char **argv){

  int listenfd, connfd, n;
  struct sockaddr_in servaddr;
  uint8_t buff[MAXLINE+1];
  uint8_t recvline[MAXLINE +1];

  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  err_n_die("socket error");

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port =htons(SERVER_PORT);  // *server Port

  if ((bind (listenfd, (SA*)&servaddr, sizeof(servaddr))) < 0 )
    err_n_die("bind Error");

  if ((listen(listenfd, 10)) < 0)
    err_n_die("Listen Error.");        // Listen and bind socket

  // server typically operates in infinite loop.

  for ( ; ; ){
    struct sockaddr_in addr;
    socklen_t addr_len;
    char client_addr[MAXLINE+1];

    //accept blocks until an incoming connection arrives
    //it returns a file descriptor to the connection
    printf ("waiting fo a connection on port%d\n",SERVER_PORT);
    fflush(stdout);

    connfd = accept(listenfd, (SA*)&addr, &addr_len); // &addr will wite the client address to the addr.
    // the client address will be in the network format and so we need to convert it to presentaion format 

    inet_ntop(AF_INET, &addr,client_addr, MAXLINE);
    printf ("The client address is %s\n",client_addr);
    // ZEro out the recieve buffer to make sure it ends up null terminated
    memset (recvline,0,MAXLINE);
    // now read the client message.

    while ((n = read (connfd, recvline, MAXLINE-1)) > 0)
    {
      fprintf(stdout, "\n%s\n\n%s",bin2hex(recvline,n), recvline);

      // hacky way to detect the end of message

      if (recvline[n-1] == '\n'){
        break;

      }
      memset(recvline, 0, MAXLINE);
    }
    if (n <0)
      err_n_die("read error");

      // Now send a response
      snprintf((char*)buff, sizeof(buff),"HTTP/1.0 200 OK\r\n\r\nHello");

      // Note normally you may want to check the result from write and close
      // in case error occurs for now i m ignoring them.

      write(connfd,(char*)buff, strlen((char*)buff));
      close(connfd);
  }
 }
