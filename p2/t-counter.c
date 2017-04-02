/*
 * Jacob Hansen
 * Takumi Nishida
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
        puts("Usage: ./t-counter <len> \"<search string>\"");
        return 1;
    }
    int len = atoi(argv[1]);
    char search[1000];
    strcpy(search, argv[2]);

    // length of buffer must be 1-1000
    if(len < 0 || len > 1000) {
        fprintf(stderr, "ERROR: buffer length must be in range [1, 1000]\n");
        return 1;
    }

    // define our socket model
    struct addrinfo hints;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;
    memset(&hints, 0, sizeof(hints));

    // create addrinfo pointer to "hold" all potential
    // address structures
    struct addrinfo *results;
    if(getaddrinfo(SERVER_NAME, SERVER_PORT, &hints, &results) != 0) {
        perror("getaddrinfo");
        return 1;
    }

    // loop until we find an address struct we can connect to
    struct addrinfo *rp = results;
    int sfd;
    while(rp != NULL) {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

        if(sfd == -1)
            continue;

        if(connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
            break;

        close(sfd);

        rp = rp->ai_next;
    }

    freeaddrinfo(results);

    // couldn't find an address to connect to
    if(rp == NULL) {
        fprintf(stderr, "ERROR: Could not connect\n");
        return 1;
    }

    // send our GET request
    if(send(sfd, REQUEST, strlen(REQUEST), 0) == -1) {
        perror("send");
        return 1;
    }

    // number of search strings found in html file
    int searchCount = 0;
    // number of characters in the last chunk received
    ssize_t charsInChunk;
    // set buffer to maximum allowed size
    char buffer[1000];

    // keep receiving and processing chunks until the html file
    // is complete
    do {
        // clear buffer
        memset(&buffer, '\0', sizeof(buffer));
        // fill buffer with 'charsInChunk' number of characters
        charsInChunk = readchunck(sfd, buffer, len);

        // we could not retreive the chunk
        if(charsInChunk == -1) {
            fprintf(stderr, "ERROR: could not retrieve chunk\n");
            return 1;
        }

        // loop through each character in received chunk to find
        // all occurrences of the substring
        unsigned int j = 0;
        for(int i=0; i<charsInChunk; i++) {
            if(search[j] == buffer[i]) {
                ++j;
                if(j == strlen(search)) {
                    ++searchCount;
                    j = 0;
                }
            } else {
                j = 0;
            }
        }
    } while(charsInChunk != 0);

    // close connection to server after transfering whole file
    close(sfd);

    printf("Number of %s instances: %i\n", search, searchCount);

    return 0;
}

ssize_t readchunck( int sockfd, void *buf, size_t len ) {
    // for some reason the function prototype we were given requires a
    // void* type, so typecast to a char* for use in recv()
    char *myBuf = (char*) buf;

    // recv() returned an error
    if(recv(sockfd, myBuf, len, 0) == -1) {
        return -1;
    }

    // return number of bytes (characters) in this chunk
    return strlen(myBuf);
}
