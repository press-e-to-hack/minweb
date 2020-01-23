#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define MAXBUF 4096

void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in *)sa)->sin_addr);

	return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
	int sock, status, msgbytes;
	struct addrinfo serv, *servinfo, *p;
	struct sockaddr_storage connector;
	char buf[MAXBUF];
	char *cls = "close\0";
	socklen_t addr_len;
	char s[INET6_ADDRSTRLEN];
	char *port = argv[1];

	memset(&serv, 0, sizeof serv);
	serv.ai_family = AF_UNSPEC;
	serv.ai_socktype = SOCK_DGRAM;
	serv.ai_flags = AI_PASSIVE;

	if ((status = getaddrinfo(NULL, port, &serv, &servinfo)) != 0)
	{
		fprintf(stderr,"Listener: getaddrinfo-> %s\n\n", gai_strerror(status));
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
		fprintf(stderr, "Listener: failed to bind socket\n\n");
		return 2;
	}

	freeaddrinfo(servinfo);

	printf("Listener: waiting to recvfrom...\n");
	while(1)
	{
		addr_len = sizeof connector;
		if ((msgbytes = recvfrom(sock, buf, MAXBUF-1, 0, (struct sockaddr *)&connector, &addr_len)) == -1)
		{
			perror("Listener: recvfrom");
			exit(1);
		}

		buf[msgbytes-1] = '\0';
		
		printf("Listener: got packet from %s\n",inet_ntop(connector.ss_family, get_in_addr((struct sockaddr *)&connector), s, sizeof s));
	
		printf("Listener: packet contains \"%s\"\n", buf);

		if ((msgbytes = sendto(sock, buf, strlen(buf), 0, (struct sockaddr *)&connector, sizeof s)) == -1)
		{
			perror("Listener: sendto");
			//continue;
		}
		//printf("%d\n\n",strcmp(buf,cls));
		printf("\n\n");
		if (strcmp(buf,cls) == 0)
		{	
			printf("Listener: Server shutdown from %s\n\n", inet_ntop(connector.ss_family, get_in_addr((struct sockaddr *)&connector), s, sizeof s));
			break;
		}
	}

	close(sock);

	return 0;
}
