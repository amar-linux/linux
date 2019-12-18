
#include"common.h"

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

char *bin2hex(const unsigned char *input, size_t len)
{
  char *result;
  char *hexlist = "0123456789ABCDEF";
  int i;
  if (input == NULL || len <= 0)
  return NULL;

  //(2 hexits +space)/chr + NULL

  int resultlength = (len*3)+1;
  result = malloc(resultlength);
  bzero(result,resultlength);

  for (i =0; i<len; i++){
    result[i*3] = hexlist[input[i] >> 4];
    result[(i*3)+1] = hexlist[input[i] & 0x0F];
    result[(i*3)+2] = ' '; // for readability
  }
  return result;
}
