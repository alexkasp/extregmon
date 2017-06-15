﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace GUI
{
    class ExtregClient
    {
        private Socket socket;

        public bool connect(ref string message)
        {
            try
            {
                IPAddress ip = IPAddress.Parse("212.193.100.65");
                IPEndPoint ipEndPoint = new IPEndPoint(ip, 7524);
                socket = new Socket(ip.AddressFamily,SocketType.Stream, ProtocolType.Tcp);
                socket.Connect(ipEndPoint);

            }
            catch(Exception ie)
            {
                message = ie.Message;
                return false;
            }
           
            return true;
        }

        public bool sendCommand(string command, ref string answer)
        {
            try
            {
                byte[] msg = Encoding.UTF8.GetBytes(command+"\r\n");
                int size = msg.Length;

                if (size != socket.Send(msg))
                {
                    answer = "wrong length was sended!!!";
                    return false;
                }
               
            }
            catch (Exception ie)
            {
                answer = ie.Message;
                return false;
            }
            return true;
        }

        public bool recvAnswer(ref string answer)
        {
            try {
                byte[] buf = new byte[2048];

                int bytesRec = socket.Receive(buf);
                    answer = Encoding.UTF8.GetString(buf, 0, bytesRec);
            }
            catch (Exception ie)
            {
                answer = ie.Message;
                return false;
            }

            return true;
        }
    }
}