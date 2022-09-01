//Local network client

using System;
using System.Net;
using System.Net.Sockets;

using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace Simple_Client
{
    class Client
    {


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
            Console.WriteLine("Enter the ip you want to use: ");
            int input = Convert.ToInt32(Console.ReadLine());

            //store and return value
            IP = address[input];

            return IP;
        }

        public static async void StartClient()
        {
            //Ip & port declaration for the socket
            IPAddress IP = Getip();
            int port = 100;

            IPEndPoint ClientEP = new IPEndPoint( IP, port );


            //Create the  TCP/IP client socket
            Socket client = new Socket(IP.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

           
            try
            {
                client.Connect(ClientEP);

                Console.WriteLine("Socket connected to {0}", client.RemoteEndPoint.ToString());

                try
                {

                    byte[] bytes = new byte[1024];
                    int bytesRec = client.Receive(bytes);

                    Console.WriteLine("Server send: " + Encoding.ASCII.GetString(bytes, 0, bytesRec));

                    //Shut down socket at both side
                    Console.WriteLine("Closing connection");


                    client.Shutdown(SocketShutdown.Both);
                    client.Close();
                }
                catch (ArgumentNullException ane)
                {
                    Console.WriteLine("ArgumentNullException: {0}", ane.ToString());
                }
                catch (SocketException se)
                {
                    Console.WriteLine("Socket Exception: {0} ", se.ToString());

                }
                catch (Exception e) {
                    Console.WriteLine("Unexpected exeption : {0} ", e.ToString());
                }



            }catch (Exception e)
            {
                Console.WriteLine(e.ToString());    
            }    

        }




    }





    internal class Program
    {
        static void Main(string[] args)
        {
            Client.StartClient();
            Console.ReadLine();
            
        }
    }
}
