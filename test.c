#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
 int main()
{
    int status;
    struct addrinfo hints;
    struct addrinfo * servinfo;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    // getaddrinfo("www.google.com",  "http" ,,);
    if((status = getaddrinfo(NULL, "3490", &hints, &servinfo))!= 0)
    {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 1;
    }
    freeaddrinfo(servinfo);
    return 0;
}