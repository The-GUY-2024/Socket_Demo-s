import socket 
import sys
import netifaces as ni

class Server:
    def __init__(self):
        self.IP = self.get_ip();
        self.port = 100;
        self.s = ""
        self.cli_socket = ""
        try:
            self.S_call();
        except KeyboardInterrupt:
            print("\nKeyboardInterrupt system closing!\n");
            self.s.close();
            print("Socket connection is close!\n")            
            sys.exit()

#this function get the interface ip address 
    def get_ip(self):
        
        #GET NETWORK INTERFACES OF THIS COMPUTER 
        interfaces = ni.interfaces()
        
        
        for t in range(len(interfaces)):
            interface_name = interfaces[t]
        #   IF INTERFACE NAME START WITH "W" (IN MY CASE )
            
            val = interface_name.startswith("w", 0,1) 
        
        #   IF VAL IS TRUE BREAK OUT THIS LOOP 
            if (val == True):
                break;
        
        #GET INTERFACE  IP ADDRESS
        ip = ni.ifaddresses(interface_name)[ni.AF_INET][0]['addr']
        
        #RETURN THE IP ADDRESS
        return ip

#THIS FUNCTION DECLARE THE PAcRAMETERS FOR SOCKET 
    def S_call(self):
        #declare socket 
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
        print("Server running at " + str(self.IP) + ":" + str(self.port));

        #Binding socket 
        self.s.bind((self.IP, self.port))

        #Listen for incoming client 
        self.s.listen(5);

        # accept connection from incoming client 
        self.cli_socket, add = self.s.accept();
        print("client connected from: " + str(add));
        
        #interact between client & server 
        self.Recv_msg();

        self.Send_msg();
        
        #close socket with client 
        self.cli_socket.close()

        #Close socket
        self.s.close()


    def Recv_msg(self):
        #Recive message from client
        msg = self.cli_socket.recv(1024).decode('utf-8'); 
        print("Client send: " + str(msg) + "\n")
    
    def Send_msg(self):
        msg = "Hello from server"
        #send data to client 
        self.cli_socket.send(msg.encode());
    


if __name__ == "__main__":
    Server();