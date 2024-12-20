#include <stdio.h>
#include <string.h>
// #include <sys/types.h>
// #include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
// #include <netinet/in.h>

int main(int argc, char * argv[])
{
    struct addrinfo hints, *res;
    int status;
    char ipstr[INET6_ADDRSTRLEN];
    if(argc != 2)
    {
        fprintf(stderr, "usuage: showip hostname\n");
        return 1;
    }
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if((status = getaddrinfo(argv[1], NULL, &hints, &res) != 0))
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }

    printf("IP addresses for %s:\n\n", argv[1]);

    for ( struct addrinfo *p = res; p != NULL; p = p->ai_next)
    {
        void *addr;
        char *ipver;
        if(p->ai_family == AF_INET)
        {
            ipver = "IPv4";
            struct sockaddr_in *ipv4 = (struct sockaddr_in *) p->ai_addr; // crazy you can do this
            addr = &(ipv4->sin_addr);
        }
        else
        {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *) p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }
        //needed to convert network format to readable format
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        printf("\t%s: %s\n", ipver, ipstr);

        /* code */
    }
    freeaddrinfo(res);
    return 0;
    
}