#ifndef __UDP_SOCKET_H_
#define __UDP_SOCKET_H_


//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------
#include <stdint.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class UDP_Socket{

public: 
using socket_fd = int;

typedef struct SocketMulticastRequestInfo{
    struct sockaddr_in multicastGroup;
    socklen_t multicastGroupLen;
    int socket;
} tSocketMulticastRequestInfo;

// Create a socket for sending the information from Cohda Hardware to the Applicatoin Unit
tSocketMulticastRequestInfo create_multicast_socket(unsigned short port, const char* address);

//Create a socket for receiving information from Applicaiton unit to Cohda Hardware
socket_fd create_unicast_socket(unsigned short port);


};



#endif //__UDP_SOCKET_H_