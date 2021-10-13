/* Simple finger server, programmed by Alexandru Goia       */
/* goia.alexandru @ gmail.com  ;  http://www.goia.go.ro/    */

/* Compile & run : gcc 3inger.c -o 3inger ; ./3inger &	    */
/* Call server : finger string_containing_{1,2,3}@my_server */
/* Or better : telnet my_server finger_port                 */

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

#define FINGER 79

int main()
{

int i;

char buffer[1024];
char *inger;

char *msg1= "Primul din cei 3 ingerasi !\n";
char *msg2= "Al doilea din cei 3 ingerasi !\n";
char *msg3= "Al treilea din cei 3 ingerasi !\n";

char *mesaj1 = "Bine ati venit pe serverul de finger al ingerasilor !\n";

int len1, len2, len3;
int lung1;

struct sockaddr_in *server = malloc(sizeof(struct sockaddr_in));
struct sockaddr_in *client = malloc(sizeof(struct sockaddr_in));
int sockfd, new_fd;
int sin_size;

len1 = strlen(msg1);
len2 = strlen(msg2);
len3 = strlen(msg3);

lung1 = strlen(mesaj1);

sin_size= sizeof (*client);
sockfd=socket(AF_INET, SOCK_STREAM, 0);

server->sin_family=AF_INET;
server->sin_port=htons(FINGER);
server->sin_addr.s_addr=INADDR_ANY;

memset(server->sin_zero, '\0', sizeof(server->sin_zero));

bind(sockfd, (struct sockaddr *) server, sizeof(*server));

while(1)
 {
 listen(sockfd, 5);
 for(i=0;i<1024;i++) buffer[i]='0';
 new_fd=accept(sockfd, (struct sockaddr *)client, &sin_size);

 write(new_fd, mesaj1, lung1);
 
 read(new_fd, buffer, sizeof(buffer));

 inger=strchr(buffer, '1');
 if(inger != NULL) 
	write(new_fd, msg1, len1);
 
 inger=strchr(buffer, '2');
 if(inger != NULL)
	write(new_fd, msg2, len2);
 
 inger=strchr(buffer, '3');
 if(inger != NULL)
	write(new_fd, msg3, len3);
  
 close(new_fd);
 }

return 0;
}
