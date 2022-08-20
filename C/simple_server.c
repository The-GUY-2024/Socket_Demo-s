#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define Port 100

//DECLARING SOCKET PARAMETERS 
int s, cli_socket, valread;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);


//DECLARE A BUFFER OF 16 KB
//Declaring a buffer of (16kb == 1024 bytes)
char buffer[1024]={0};
//Declaring the text that will be send over network
char* hello = "Hello, from Server";


// Function for socket declaration
void Socket(void);


void Server(){
    Socket();

    //Declare parameter for address 

    // Declare tcp  parameter
    address.sin_family = AF_INET;

    //Declare the ip address for the server
    address.sin_addr.s_addr = INADDR_ANY;

    //Declare the port for the server
    address.sin_port = htons(Port);

    // BIND ADDRESS & PORT 
    if ( bind(s, (struct sockaddr*) &address, sizeof(address)) < 0)
    {
        perror(" Error happend at binding to address & port !!!");
        exit(EXIT_FAILURE);
    }

    //Listening for incomming connection
    if (listen(s,3) < 0) // We onli recive 3 attemps to connect
    {   
        perror("Error at listening for incomming connection! ");
        exit(EXIT_FAILURE);
    }

    // ACCEPT CLIENT AND STORE INFORMATION 
    if( ( cli_socket = accept(s, (struct sockaddr*)&address, 
        (socklen_t*)&addrlen)) < 0)
    {
        perror("error at accepting client to extablish connection");
        exit(EXIT_FAILURE);
    }

    //Recive data from client 
    valread = read(cli_socket, buffer, 1024);
    printf( "client send: %s\n" , buffer);

    //Send data to client 
    send(cli_socket, hello, strlen(hello), 0);
    printf("message send to client\n");


    // Close the connection whit the client 
    close(cli_socket);
    //Close the listening socket
    shutdown(s, SHUT_RDWR);
}

void Socket(){
    
    //Declare socket to (server_fd)
    s = socket(AF_INET, SOCK_STREAM, 0);
    
    //Check for error in socket
    if(s == 0){
        perror("Error in socket (clossing system)! ");
        exit(EXIT_FAILURE);
    }

    //Attache socket to the declare port 
    if(setsockopt( s , SOL_SOCKET, 
                   SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        printf("Attaching port to socket error");
        exit(EXIT_FAILURE);
    }

}


int main(int argc, char const* argv[]){

    Server();


    return EXIT_SUCCESS;   
}