/*
 * Student A Name
 * Student B Name
 * CSCI 446
 * Spring 2016
 *
 * This template provides the framework you need for program 1. Complete the functions
 * defined and create any you feel are neccessary. stream-talk-client.c on Learn will
 * prove useful.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define SERVER_NAME "www.ecst.csuchico.edu"
#define SERVER_PORT "80"
#define REQUEST "GET /~ehamouda/file.html HTTP/1.0\n\n"


/***************************************************************
 * Arguments: same as recv(2)
 * Return:-1 on error or bytes received
 *
 * Receive len bytes of data into array buf from socket sockfd. Always receive len bytes
 * of data unless the socket closes. The return value will fall into one of three cases:
 *   (1) on success the return value equals len
 *   (2) on error the return value equals -1
 *   (3) if the socket closes without receiving len bytes, then return the number
 *       actually received, which may be zero
 ***************************************************************/
ssize_t readchunck( int sockfd, void *buf, size_t len );


int main( int argc, char *argv[] ) {
    // parse CLI args
    if(argc != 3) {
        printf("Usage: ./t-counter <len> \"<search string>\"\n");
        return 1;
    }
    int len = atoi(argv[1]);
    char searchStr[100];
    strcpy(searchStr, argv[2]);

    // connect to server
    struct hostent* serv = gethostbyname(SERVER_NAME);
    if(serv == NULL) {
        printf("ERROR: could not connect to host at %s\n", SERVER_NAME);
        return 1;
    }

    

    return 0;
}

ssize_t readchunck( int sockfd, void *buf, size_t len ) {

    /* Define readchunck to return exactly len bytes unless an error occurs or the socket closes. 
*/
    
}












