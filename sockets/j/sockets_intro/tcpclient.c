 #include<stdio.h>
 #include<stdlib.h>
 #include<sys/socket.h>
 #include<sys/types.h>
 #include<signal.h>
 #include<string.h>
 #include<unistd.h>
 #include<arpa/inet.h>
 #include<stdarg.h>
 #include<errno.h>
 #include<fcntl.h>
 #include<sys/time.h>
 #include<sys/ioctl.h>
 #include<netdb.h>

 #define SERVER_PORT 80

 #define MAXLINE 4096


// Standard HTTP port.  server port were we are connecting.
 #define SA struct sockaddr

 void err_n_die(const char *fmt, ...);

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

 void err_n_die(const char *fmt, ...){

   int errno_save;
   va_list ap;

   // any system or library call can set errno so we need to save it now.

   errno_save = errno ;

   // print the fmt + args to standard out

   va_start(ap, fmt);
   vfprintf(stdout, fmt, ap);
   fprintf(stdout,"\n");
   fflush(stdout);

   // print out error message is errno was set.
   if (errno_save !=0)
   {
     fprintf(stdout, "(errno = %d) : %s\n",errno_save,
     strerror(errno_save));
     fprintf(stdout,"\n");
     fflush(stdout);
   }
   va_end(ap);
// this is the end and_die part terminate with an error.
   exit(1);
 }
