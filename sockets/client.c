#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>

/*
 * client side flow
 * socket()  -->  connect()  -->  write()/read()  -->  close
 */

int main(){
    //creating a socket
    int network_socket;

    // type: SOCK_STREAM = tcp or SOCK_DGRAM = udp 
    // domain: AF_INET for ipv4
    // basically declaring a socket
    // socket(domain, type, protocol)
	network_socket = socket(AF_INET,SOCK_STREAM,0);

    // cheking for erros
    if(network_socket < 0){
        printf("socket could not be created\n");
        return 0;
    }

    //specifying address for socket to connect to
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9000);
    server_address.sin_addr.s_addr = INADDR_ANY;


    int connect_status = connect(network_socket,(struct sockaddr*)&server_address,sizeof(server_address));
    //check for error with the connection
    if(connect_status==-1){
        printf("there was an error connecting to the server");
    }

    //receive data from server
    char server_response[256];
    recv(network_socket,&server_response,sizeof(server_response),0);
    printf("data from server:%s\n",server_response);

    close(network_socket);
    return 0;
}