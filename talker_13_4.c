/* Below is the talker.c file */
/*
** talker.c 
** Command = ./talker localhost "hello world"
*/  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define MYPORT 4950             // the port users will be connecting to
 
typedef struct {
        int field1;
        char field2[16];
} t_data;
 
int main (int argc, char *argv[]) 
{
 
    int sockfd;
 
    struct sockaddr_in their_addr;      // connector's address information
    struct hostent *he;
 
    int numbytes;

	t_data my_object;
	my_object.field1 = 1;
	strncpy(my_object.field2, "hello world", 12);
 
    if (argc != 3)
    {
        fprintf (stderr, "usage: talker hostname message\n");
        exit (1);
    }
 
    if ((he = gethostbyname (argv[1])) == NULL)
    {                           // get the host info
        perror ("gethostbyname");
        exit (1);
    }
 
    if ((sockfd = socket (AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror ("socket");
        exit (1);
    }
 
    their_addr.sin_family = AF_INET;    // host byte order
    their_addr.sin_port = htons (MYPORT);       // short, network byte order
    their_addr.sin_addr = *((struct in_addr *) he->h_addr);
 
    memset (&(their_addr.sin_zero), '\0', 8);   // zero the rest of the struct
	
	//printf(sizeof(struct t_data my_object));
	int ix=0;
	while(ix++ < 10){
		if ((numbytes = sendto (sockfd, &my_object, sizeof(my_object), 0, 
                            (struct sockaddr *) &their_addr,
                            sizeof (struct sockaddr))) == -1)
    {
        perror ("sendto");
        exit (1);
    }
	my_object.field1++;
    printf ("sent %d bytes to %s\n", numbytes,
		inet_ntoa (their_addr.sin_addr));		
	}
 

	
    close (sockfd);
    return 0;
 
}
