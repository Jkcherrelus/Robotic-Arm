using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.IO;
using System.IO.Ports;
using System.Timers;

namespace Serial_Communication
{
    class Program
    {
        SerialPort currentPort;
        bool portFound;
        private static int turnUp = 0;

        public static void Main(string[] args)
        {
            Console.WriteLine("The beginning...");
            Program program = new Program();
            program.SetComPort();
            int servo = 0;
            int direction = 0;
            //takes servo and turning direction as parameters
            //sends a message to the arduino
            
             //   Console.WriteLine("Choose servo: ");
               // servo = Console.Read();
                //Console.WriteLine("Choose direction: ");
                //direction = Console.Read();
                program.sendMessage(0, turnUp);
                program.sendMessage(1, turnUp);
                program.sendMessage(2, turnUp);
                program.sendMessage(3, turnUp);
                program.sendMessage(4, turnUp);
            program.sendMessage(0, turnUp);
            program.sendMessage(1, turnUp);
            program.sendMessage(0, turnUp);
            program.sendMessage(3, turnUp);
            program.sendMessage(4, turnUp);
            program.sendMessage(0, turnUp);
            program.sendMessage(2, turnUp);
            program.sendMessage(2, turnUp);
            program.sendMessage(2, turnUp);
            program.sendMessage(4, turnUp);
            Console.WriteLine("The port " + program.currentPort.PortName + " is " + program.currentPort.IsOpen);
                program.currentPort.Close();
                Console.WriteLine("The port " + program.currentPort.PortName + " is " + program.currentPort.IsOpen);
                Console.WriteLine("All ports closed.");
                Console.Read();
            
        }
        //set the correct port
        private void SetComPort()
        {
            try
            {
                string[] ports = SerialPort.GetPortNames(); 
                foreach (string port in ports)
                {
                    Console.WriteLine("Port number is " + port);
                    currentPort = new SerialPort(port, 115200);
                    if (DetectArduino())
                    {
                        portFound = true;
                        break;
                    }
                    else
                    {
                        portFound = false;
                    }
                }
            }
            catch (Exception e)
            {
            }
            //Console.Read();
        }
        //find the correct port
        private bool DetectArduino()
        {
            try
            {
                //The below setting are for the Hello handshake
                byte[] buffer = new byte[5];
                buffer[0] = Convert.ToByte(16);
                buffer[1] = Convert.ToByte(128);
                buffer[2] = Convert.ToByte(0);
                buffer[3] = Convert.ToByte(0);
                buffer[4] = Convert.ToByte(4);

                int intReturnASCII = 0;
                char charReturnValue = (Char)intReturnASCII;

                currentPort.Open();
                currentPort.Write(buffer, 0, 5);
                System.Threading.Thread.Sleep(1000);

                int count = currentPort.BytesToRead;
                string returnMessage = "";
                while (count > 0)
                {
                    intReturnASCII = currentPort.ReadByte();
                    returnMessage = returnMessage + Convert.ToChar(intReturnASCII);
                    count--;
                }
                // ComPort.name = returnMessage;
                Console.WriteLine("The arduino message is " + returnMessage);
                //currentPort.Close();

                if (returnMessage.Contains("HELLO FROM ARDUINO"))
                {
                    Console.WriteLine("Arduino Detected");
                    return true;
                }
                else
                {
                    Console.WriteLine("Arduino Not Detected");
                    return false;
                }
            }
            catch (Exception e)
            {
                return false;
            }
        }

        //send message
        public void sendMessage(int servo,int direction)
        {
            byte[] buffer = new byte[5];
            buffer[0] = Convert.ToByte(16);
            buffer[1] = Convert.ToByte(127);
            buffer[2] = Convert.ToByte(servo);
            buffer[3] = Convert.ToByte(direction);
            buffer[4] = Convert.ToByte(4);
            try
            {
                //currentPort.Open();
                Console.WriteLine("The port is open " + currentPort.IsOpen);
                currentPort.Write(buffer, 0, 5);
                Thread.Sleep(2000);
                int intReturnASCII = 0;

                char charReturnValue = (Char)intReturnASCII;

                int count = currentPort.BytesToRead;
                string returnMessage = "";
                while (count > 0)
                {
                    intReturnASCII = currentPort.ReadByte();
                    returnMessage = returnMessage + Convert.ToChar(intReturnASCII);
                    count--;
                }
                Console.WriteLine("The return message is " + returnMessage);
                //currentPort.Close();
            }
            catch(Exception e)
            {
                Console.WriteLine();
            }
        }


    }
}
