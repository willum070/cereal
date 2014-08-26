cereal
======

A super-simple C# console app for testing serial I/O. I wrote Cereal to be very simple and yet provide some nice functionality so that it can be extended to do more stuff. Here is what Cereal does:

- Opens a serial connection to the specified COM port.
- Monitors that COM port using an event handler, printing the data to the console.
- Accepts user input for the available commands. The actual commands are defined in the corresponding Arduino sketch.

