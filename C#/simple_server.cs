//unfinish

using System;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Simple_Server
{

    class Server
    {


        //This fuction get all Ip from the host and display them
        //Let the user select the preffered ip 
        public static IPAddress Getip()
        {

            //Definition of the ip for the socket
            IPAddress IP;
            

            //this method retrive all ip of this host, using the name of the host
            String HostName = Dns.GetHostName();
            IPHostEntry myIP = Dns.GetHostEntry(HostName);

            IPAddress[] address = myIP.AddressList;


            for (int i = 0; i < address.Length; i++)
            {
                string add = address[i].ToString();
                Console.WriteLine(i + ") IP Address: " + add);

            }
            //Get user input for ip in use
            Console.WriteLine("Enter the ip you want to use: " );
            int input = Convert.ToInt32(Console.ReadLine());

            //store and return value
            IP = address[input];

            return IP;
        }

        // This function declare the socket parameters for the server 

        public static async void StartServer()
        {
            //IP And port declaration for socket
            
            //Storing the ip selected in (`IP`)
            IPAddress IP = Getip();
            int port = 100;

            //Socket IP & PORT 
            IPEndPoint LEP = new IPEndPoint(IP, port); 
            try {
                //Create the socket server that will use tcp protocole
                Socket Server = new Socket(IP.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

                Console.WriteLine("The server is open at " + LEP);
                //A Socket must be associated with and endpoint using the bind method 
                Server.Bind(LEP);

                //Listen for incoming client on server socket 
                Server.Listen(10);

                //Accepting client to the server socket 
                var handler = await Server.AcceptAsync();


                Console.WriteLine("Client connected from: " + handler);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }
    }



    internal class Program
    {
        static void Main(string[] args)
        {
            Server.StartServer();
            Console.ReadLine();
        }
    }
}
