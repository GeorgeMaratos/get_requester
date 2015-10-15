#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define REQ_SIZE 150
#define URL_SIZE 40
#define BUF_SIZE 1000000
#define PORT "80"

struct addrinfo hint = {0}, *hints = NULL, *results = NULL; 

int main(int argc, char **argv) {  //argv[1] is the site to request from
  int i = 0, j = 0, sock = 0;
  FILE *f = fopen("out_file.txt", "w");
  char get_request[REQ_SIZE], url[URL_SIZE] = {0}, page[URL_SIZE] = {0},
	host[URL_SIZE] = {0}, buffer[BUF_SIZE] = {0};
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
  sprintf(get_request,"GET %s HTTP/1.0\r\nHost: %s\r\n\r\n", page, host);
  printf("get_request: %s\n", get_request);
  hints = &hint;
  hint.ai_family = AF_UNSPEC;
  hint.ai_socktype = SOCK_STREAM;
  hint.ai_flags = AI_PASSIVE;
  if(getaddrinfo(host, PORT, hints, &results)) {
    printf("getaddrinfo failed\n");
    return 1;
  }
  if((sock = socket(results->ai_family, results->ai_socktype,
	 results->ai_protocol)) < 0) {
    printf("socket failed\n");
    return 1;
  }
  if(connect(sock,results->ai_addr, results->ai_addrlen)) {
    printf("connect failed\n");
    return 1;
  }
  if(send(sock, get_request, REQ_SIZE, 0) < 0) {
    printf("send failed\n");
    return 1;
  }
  printf("Waiting for result\n");
  recv(sock, buffer, BUF_SIZE, 0);
  for(i=0;i<BUF_SIZE;i++) {
    fprintf(f,"%c", buffer[i]);
  }
  freeaddrinfo(results);
  fclose(f);
  return 0;
}
