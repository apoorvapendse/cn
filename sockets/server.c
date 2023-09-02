#include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

#include <unistd.h>         // for read()
#include <sys/socket.h>     // for sockaddr
#include <sys/types.h>
#include <netinet/in.h>     // for sockaddr_in

/*
 * server side flow
 * socket() --> bind() --> listen() --> accept() --> read()/write() -- close()
 */

void main(){
    // creating a socket
    int network_socket;

    // type: SOCK_STREAM = tcp or SOCK_DGRAM = udp 
    // domain: AF_INET for ipv4
    // basically declaring a socket
    // socket(domain, type, protocol)
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // cheking for erros
    if(network_socket < 0){
        printf("socket could not be created\n");
        return;
    }
    
    //specifying address for server
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9000);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // telling the socket where to connect
    // bind(socket, struct sockaddr, sizeof(sockaddr))
    int server_addr_size = sizeof(server_address);
    int bindStatus = bind(network_socket, (struct sockaddr*) &server_address, server_addr_size);
    if(bindStatus < 0){
        printf("binding failed\n");
        return;
    }

    // prepare to accept incoming connections
    // listen(socket, no of connections)
    listen(network_socket, 5);

    // accept connection
    // struct client_address used to store incoming clients data
    struct sockaddr_in client_address;
    int client_address_size =  sizeof(client_address);
    int new_socket = accept(network_socket, (struct sockaddr*) &client_address, &client_address_size);

    if(new_socket < 0){
        printf("error on accept\n");
        return;
    }

    // sending data
    char buff[256] = "arey vedya!!";
    int n = send(new_socket, buff, 256, 0);

    if(n < 0){
        printf("error on writing\n");
        return;
    }
    close(new_socket);
    close(network_socket);
    return;
 }