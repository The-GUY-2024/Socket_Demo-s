#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define Port 100


//DECLARING SOCKET PARAMETERS
int s = 0, valread, client_fd;
struct sockaddr_in serv_addr;

//declaring buffer for text
char* hello = "HELLO from Client";
//Declaring a buffer of (16kb == 1024 bytes)
char buffer[1024] = {0};

// Function for socket declaration
void Socket(void);


void Client(){
    Socket();

    //Send (message) data to the server
    send(s,hello, strlen(hello), 0);
    printf("Hello Message sent\n");

    //Recive message from server
    valread = read(s, buffer, 1024);
    printf("%s\n", buffer);

    //Clossing the connection of socket
    close(client_fd); 

}

void Socket(){
    //Declare the socket for client connection
    s = socket(AF_INET, SOCK_STREAM, 0);

    //Check for error in socket declaration
    if (s == 0){
        perror("Error in socket Declaration (closing system) ");
        exit(EXIT_FAILURE);
    }    


    //Declare the port and socket family
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(Port);

    // declare the ip address for server
    //!!! In my case the server and client are running in a local network
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) 
    {
        printf("\n Invalid address enter (server is not open on this address!) ");
        exit(EXIT_FAILURE);
    }

    //Connect to the declare address & port 
    if( client_fd = connect( s, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0 )
    {
        printf("\n Failure at connecting to server (check the address )");
        exit(EXIT_FAILURE);
    }
}
int main(int argc, char const* argv[])
{
    Client();
    return EXIT_SUCCESS;
}