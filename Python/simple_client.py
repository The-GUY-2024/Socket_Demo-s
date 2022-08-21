import socket 
import sys
import netifaces as ni


class Client:
    def __init__(self):
        try:
            self.address = ("192.168.0.2",100)
            self.s = ""
            self.S_call();


        except KeyboardInterrupt:
            print("\nKeyboardInterrupt system closing!\n");
            self.s.close();
            print("Socket connection is close!\n")            
            sys.exit()

    
    def S_call(self):
        #Declaring socket 
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # connect to server 
        self.s.connect(self.address);
        print("Connecting to server at: " + str(self.address[0]) + ":" + str(self.address[1]))

        #Interact between client & server 
        self.Send_msg();

        self.Recv_msg();

#CLOSE SOCKET AFTER INTERACTION
        self.s.close()

# Send message to server
    def Send_msg(self):
        msg = "Hello from client"
        self.s.send(msg.encode('utf-8'));

# Recive message from server
    def Recv_msg(self):
        msg = ""
        msg = self.s.recv(1024).decode('utf-8');

        print("Server send: " + str(msg) + "\n");

if __name__ == "__main__":
    Client();