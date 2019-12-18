#include"common.h"
#include<string.h>

int main (int argc, char **argv){

  int sockfd, n;
  int sendbytes;
  struct sockaddr_in servaddr;
  char sendline[MAXLINE];
  char recvline[MAXLINE];

  if (argc !=2)
    err_n_die("usage: %s<server address>",argv[0]);

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
     err_n_die("Error while creating socke !");

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERVER_PORT);  /* Chat server */

  if (inet_pton(AF_INET, argv[1],&servaddr.sin_addr) <= 0)
   err_n_die("inet_pton error for %s",argv[1]);

  if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))< 0)
   err_n_die("Connect failed !");

   // We are connected prepair the message.

   sprintf(sendline,"GET /HTTP/1.1\r\n\r\n");  // get coomand to give me a root page version1.1
   sendbytes =strlen(sendline);

   //send the request and make sure you have sent it cal
   // this code is a bit fragile since it bails if only some of the bytes are sent
   //normally you would want to retry unless the return value was -1

   if (write(sockfd,sendline,sendbytes)!= sendbytes)
     err_n_die("write Failed !");

   memset(recvline, 0, MAXLINE);

   while((n = read(sockfd, recvline, MAXLINE- 1))> 0)
   {
     printf ("%s",recvline);
   }
   if (n < 0)
     err_n_die("read error");

   exit(0);   // end sucessfully.
   printf ("\n");


}
