#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <stdio.h>

#define port    2020
#define timeout 3

int main(int argc, char **argv)
{
	int listenfd;
	int connfd;
	int i = 1;
	char buffer[512];
	int flags, ret, j;

	struct sockaddr_in servaddr;
	struct pollfd fds[1024];
	
	fds[0].fd = STDIN_FILENO;
	fds[0].events = POLLIN;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);

	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	listen(listenfd, 16);

	flags = fcntl(listenfd, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(listenfd, F_SETFL, flags);

	while(1) {
		connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);
		
		if(connfd >= 0) {
				fds[i].fd = connfd;
				fds[i].events = POLLOUT;
				i++;
				}
		ret = poll(fds, i, timeout * 1000);

		if(fds[0].revents & POLLIN) {
				puts("fratele din C spune celorlalti>");
				read(STDIN_FILENO, buffer, sizeof(buffer));
				for(j = 1; j<=i ; j++)
				 	if(fds[j].revents & POLLOUT)   
				  		write(fds[j].fd, buffer, sizeof(buffer));
				bzero(&buffer, sizeof(buffer));
		}
	}
	
	return 0;
}
