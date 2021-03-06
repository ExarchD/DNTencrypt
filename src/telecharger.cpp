#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "objects.h"
#include <sys/types.h>
#ifdef __WIN32__
#define __WIN32__WINNT
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netdb.h>
#include <encrypter.h>
#endif
#define BUF_SIZE 5000
#include <iostream>
using namespace std;

int check_serverstatus(const char* host_int, int port_int)
{

    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;
    char port[256];
    sprintf(port, "%d", port_int);

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

        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1){
            return 1;
            break;                  /* Success */
        }

        close(sfd);
    }

    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not connect\n");
        return 0;
    }
}




int sender(const char* host_int, int port_int, const char* msg, int length)
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s, j;
    size_t len;
    ssize_t nread;
    char buf[length];
    char port[256];
    sprintf(port, "%d", port_int);

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

#ifdef __WIN32__

        int iResult;
        WSADATA wsaData;
        sockaddr_in RecvAddr;

        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        char SendBuf[1024];
        int BufLen = 1024;
        RecvAddr.sin_family = AF_INET;
        unsigned short Port = 6655;
        RecvAddr.sin_port = htons(Port);
        RecvAddr.sin_addr.s_addr = inet_addr("192.168.1.1"); //this is likely a problem...

        cout << msg << endl;
        iResult = sendto(sfd,
                msg, BufLen, 0, (SOCKADDR *) & RecvAddr, sizeof (RecvAddr));
        if (iResult == SOCKET_ERROR) {
            wprintf(L"sendto failed with error: %d\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }
#else

        if (write(sfd, msg, len) != len) {
            fprintf(stderr, "partial/failed write\n");
            exit(EXIT_FAILURE);
        }
#endif   
        //        fwrite (msg, , 1, stdout);

        // add loop so that we can send in 512 chunks
        // possibly remove my 'fix' so that the client app
        // recieves the data in 512 byte chunks
        // not sure if that's ideal or not
        // should check what the best sized chunk of data is

        nread = read(sfd, buf, length);
        if (nread == -1) {
            perror("read");
            cout << "MESSAGE NOT SENT" << endl;
            cout << "please double check your server settings" << endl;
            return 1;
        }

        //    printf("Received %ld bytes: %s\n", (long) nread, buf);
    }
    string encrypt_return=string(buf);
    if (encrypt_return == "SUCCESS") return 0;
    if (encrypt_return == "Failure") return 1;
    if (encrypt_return.find("-----BEGIN PGP MESSAGE-----") == 0)
    {
        string delimiter = ";";
        string finalmsg=encrypt_return.substr(0, encrypt_return.find(delimiter));
        database_insert(finalmsg);
        msg_to_gpgme_data(finalmsg);
    }

    //    if (buf == "exists");
    msg_index++;
    return 0;
    //exit(EXIT_SUCCESS);
}
