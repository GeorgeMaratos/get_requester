#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define REQ_SIZE 150
#define URL_SIZE 20

int main(int argc, char **argv) {  //argv[1] is the site to request from
  int i = 0, j = 0;
  char get_request[REQ_SIZE], url[URL_SIZE] = {0}, page[URL_SIZE] = {0}, host[URL_SIZE] = {0};
  sscanf(argv[1], "http://%s\n", url);
  while(url[i] != '/') {
    host[i] = url[i];
    i++;
  }
  while(i < URL_SIZE) {
    page[j] = url[i];
    j++;
    i++;
  }
  printf("%s|%s\n", host, page);
  return 0;
}
