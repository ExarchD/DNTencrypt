#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "objects.h"
#include <gpgme.h>
#define BUF_SIZE 512
#include <iostream>
using namespace std;

int
sender(const char* host_int, int port_int, const char* msg, int length)
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s, j;
    size_t len;
    ssize_t nread;
    char buf[length];
//    char host[256];
//    sprintf(host, "%d", host_int);
    char port[256];
    sprintf(port, "%d", port_int);

    /* Obtain address(es) matching host/port */

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */

    s = getaddrinfo(host_int, port, &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    /* getaddrinfo() returns a list of address structures.
       Try each address until we successfully connect(2).
       If socket(2) (or connect(2)) fails, we (close the socket
       and) try the next address. */

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype,
                     rp->ai_protocol);
        if (sfd == -1)
            continue;

        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
            break;                  /* Success */

        close(sfd);
    }

    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not connect\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);           /* No longer needed */
    /* Send remaining command-line arguments as separate
       datagrams, and read responses from server */
    for (j = 3; j < 4; j++) {
        len = strlen(msg);
                /* +1 for terminating null byte */
          //cout << len << " " << length << endl;
        if (len  != len) {
            fprintf(stderr,
                    "Ignoring long message in argument %d\n", j);
            continue;
        }

        if (write(sfd, msg, len) != len) {
            fprintf(stderr, "partial/failed write\n");
            exit(EXIT_FAILURE);
        }
        
//        fwrite (msg, , 1, stdout);


// add loop so that we can send in 512 chunks
// possibly remove my 'fix' so that the client app
// recieves the data in 512 byte chunks
// not sure if that's ideal or not
// should check what the best sized chunk of data is

        nread = read(sfd, buf, length);
	cout << buf << endl;
        if (nread == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

    //    printf("Received %ld bytes: %s\n", (long) nread, buf);
    }
   return len;
    //exit(EXIT_SUCCESS);
}
