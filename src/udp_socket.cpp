#include<iostream>
#include <cstring>
#include <errno.h>
#include <memory>

#include "udp_socket.h"

// Create a multicast socket for sending the information from Cohda Hardware to the Applicatoin Unit
UDP_Socket::SocketMulticastRequestInfo UDP_Socket::create_multicast_socket(unsigned short port, const char* address){

    tSocketMulticastRequestInfo multicastRequestInfo;

    int multicastGroupSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (multicastGroupSocket < 0) {
        std::cout << "ERROR opening multicast socket"<< std::endl;
        exit(1);
    }

    // Eliminates "ERROR on binding: Address already in use" error
    int optval = 1;
    if (setsockopt(multicastGroupSocket, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int)) < 0) {
        std::cout << "ERROR setting multicast socket options"<< std::endl;
        exit(1);
    }

    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = inet_addr(address);
    sockAddr.sin_port = htons(port);

    if (bind(multicastGroupSocket, (struct sockaddr*)&sockAddr, sizeof(sockAddr)) < 0) {
        std::cout << "ERROR on binding port while creating multicast socket, port: "<< port << std::endl;
        exit(1);
    }

    // Initialize the multicastRequestInfo structure
    multicastRequestInfo.multicastGroup = sockAddr;
    multicastRequestInfo.multicastGroupLen = sizeof(sockAddr);
    multicastRequestInfo.socket = multicastGroupSocket;

    std::cout << "multicastRequestInfo.socket: " << multicastRequestInfo.socket << std::endl;
    return multicastRequestInfo;
}

//Create a socket for receiving information from Applicaiton unit to Cohda Hardware
UDP_Socket::socket_fd UDP_Socket::create_unicast_socket(unsigned short port){

    int sock_receiv;

    sock_receiv = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_receiv < 0) {
        std::cout << "Creating socket failed" << std::endl;
        exit(1);
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to the specified address and port
    if (bind(sock_receiv, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cout << "Binding socket failed for port: " << port << std::endl;
        exit(1);
    }

    std::cout << "Unicast socket created for port: " << port << ", with soc fd: " << sock_receiv << std::endl;
    return sock_receiv;
}
