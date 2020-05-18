#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define ERROR -1
#define MAX_BUF 4096
#define MAX_CLI 5

void *get_in_addr(struct sockaddr * sa)
{
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in *)sa)->sin_addr);
	
	return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void *usage()
{
	printf("Usage: minweb [port]\n\n");
}

int main(int argc, char **argv)
{

	if(argc <= 1 || argc > 2)
	{
		usage();
		return 0;
	}

	const char *const port = argv[1];

	printf("port:%s\n\nargc:%d\n\n",port,argc);

	return 0;

}
