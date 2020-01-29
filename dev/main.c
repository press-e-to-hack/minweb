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


//Util Function
void *get_in_addr(struct sockaddr * sa)
{
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in *)sa)->sin_addr);
	
	return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void *usage()
{
	printf("Usage: ./minWeb <port # to listen on>\n\n");
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


/*
int main(int argc, char **argv)
{
	int sock, cli, msgbytes, status;
	struct addrinfo serv, *servinfo, *p;
	struct sockaddr_storage connector;
	char s[INET6_ADDRSTRLEN];
	char buf[MAX_BUF];
	char *port = argv[1];
	socklen_t addr_len;

	memset(&serv, 0, sizeof serv);
	serv.ai_family = AF_UNSPEC;
	serv.ai_socktype = SOCK_STREAM;
	serv.ai_flags = AI_PASSIVE;

	if ((status = getaddrinfo(NULL, port, &serv, &servinfo)) != 0)
	{
		fprintf(stderr,"Listener: getaddrinfo->%s\n\n",gai_strerror(status));
		return 1;	
	} 
	
	for (p = servinfo; p != NULL; p = p->ai_next)
	{
		if ((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
		{
			perror("Listener: socket");
			continue;
		}
		if (bind(sock, p->ai_addr, p->ai_addrlen) == -1)
		{
			close(sock);
			perror("Listener: bind");
			continue;
		}
		break;
	}

	if (p == NULL)
	{
		fprintf(stderr, "Listener: failed to bind to socket\n\n");
		return 2;
	}

	freeaddrinfo(servinfo);

	if (listen(sock, MAX_CLI) == -1)
	{
		perror("Listener: listen");
		return 1;
	}

	puts("Listener: waiting to recv data...");

	while(1)
	{
		addr_len = sizeof connector;
		if ((cli = accept(sock, (struct sockaddr *)&connector, &addr_len)) == -1)
		{
			perror("Listener: accept");
			return 1;
		}

		printf("Listener: New connection from port %d and IP %s\n", ((struct sockaddr_in *)&connector)->sin_port, inet_ntop(connector.ss_family, get_in_addr((struct sockaddr *)&connector), s, sizeof s));

		msgbytes = 1;

		while(msgbytes)
		{
			msgbytes = recv(cli, buf, MAX_BUF, 0);
			buf[msgbytes] = '\0';
			msgbytes++;

			if(msgbytes)
			{
				send(cli, buf, msgbytes, 0);
				printf("Sent msg: %s\n", buf);
			}
		}

		printf("Listener: client disconnected\n\n");
		close(cli);
	}
	
	return 0;
}
*/
