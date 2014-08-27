/********************************************************
 * Cereal:
 * A dirt-simple console app to test serial connections.
*********************************************************/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.IO.Ports;

namespace cereal
{
    class Program
    {
        static void Main(string[] args)
        {
            string port = "COM8";
            SerialPort sp = new SerialPort(port, 9600, Parity.None, 8, StopBits.One);

            // Declare an event handler to fire on data received.
            sp.DataReceived += sp_DataReceived;

            try
            {
                // Open the serial port (close first if it's already open).
                if (sp.IsOpen == true) sp.Close();
                sp.Open();

                Console.WriteLine("Port {0} opened.", port);                

                sp.ReadTimeout = 1000;

                // An indefinite loop to get user input.
                while (true)
                {
                    Console.Write("Enter a command ('?', 'v', 'exit'): "); // Prompt
                    string input = Console.ReadLine(); // Get the input string

                    if (input == "exit")
                    {
                        break;
                    }

                    // Enclose the command in brackets and send to the serial port.
                    sp.Write("[" + input + "]");

                    // Pause for 2 seconds to wait for response. Quick and dirty!
                    Thread.Sleep(2000);
                }                
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex);
                Console.ReadLine();
            }

        }

        // Event handler method, fired whenever serial data is received.
        static void sp_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort spL = (SerialPort)sender;
            string raw = spL.ReadTo("]");
            Console.WriteLine(raw.Remove(0, 1));
        }

    }
}
