#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <sstream>
#include <string>
#include <arpa/inet.h>


class Client{


    public:
        int main()
        {
            //Declare the socket parameter
            Call_socket();


            //Send message to server
            Send_msg();

            //recive message from server
            recv_msg();


            //Close the socket 
            Close_socket();
            return 0;
        }




    private:
    //Declaring socket parameter 
        int S,n;        
        struct sockaddr_in serverAddr;
        socklen_t addrLen = sizeof(struct sockaddr_in);



        //Declaring the server ip address
        char Ip[20] = "192.168.0.7"; 
        //Declaring the server port 
        int Port = 100;


        void Call_socket(){
            if ((S = socket(PF_INET, SOCK_STREAM, 0)) <0) {
                std::cerr << "Error at declaring socket" << std::endl;
                exit(1);
            } 
            std::cout << "Socket has being declare" << std::endl;


            // Declaring the ip ,port & packege family 
            serverAddr.sin_family = PF_INET;
            serverAddr.sin_addr.s_addr = inet_addr(Ip);
            serverAddr.sin_port = htons(Port);

            if (connect(S, (sockaddr*)&serverAddr, addrLen)< 0){
                std::cerr << "Error at creating connection between socket !" << std::endl;        
                exit(1);
            }
    
            std::cout << "Connection between client & server has been established" << std::endl;

        }

        //Error message function (GOOD PRACTICE)
        void error(const char *msg){
            perror(msg);
            exit(1);
        }

        //Send message to the server
        void Send_msg(){
            char msg[25] = "Hello from client";
            send(S,msg,1024,0);
        }
    
        //Recive message from the server
        void recv_msg(){
            char buffer[1024];
            bzero(buffer,1024);
            n = read(S, buffer, 1024);
            if (n < 0){
                Close_socket();
            }
            std::string s(buffer);
            std::cout << "Server Send: " << s <<std::endl;

        }

        //Close socket and exit 
        void Close_socket(){
            close(S);
            error(" Closing connection with server ");         
        }

};








int main(int argc, char** argv){

    Client client;

    client.main();
    


    return 0;
}