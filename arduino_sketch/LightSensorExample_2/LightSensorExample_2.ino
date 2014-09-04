/*
  Light sensor example.
*/

//int led = 13;
int temt6000Pin = 0;
int numCharRead = 0;
char incomingData[20];
boolean stream = false;

// the setup routine runs once when you press reset:
void setup() {                
    //Setup the serial port
    Serial.begin(9600);
}

// Infinite loop to get user input:
void loop() {
    if (Serial.available() > 0) {
        numCharRead = Serial.readBytesUntil(']',  incomingData, 19);
        processCommands(numCharRead);        
    }
    
    // Send continuously if the 'stream' flag is set to 'true'.
    if(stream) {
      sendReading();
      delay(100);
    }
}

// Send out a reading.
void sendReading() {
  Serial.print("[");
  Serial.print(analogRead(temt6000Pin));
  Serial.print("]");
}

int processCommands(int numCharRead ) {
  
   if (numCharRead < 2)  { //need at least '[' and one other character
       Serial.print("[!Badly formatted command]");  //! to indicate text string
       return -1; //skip the rest
     }
  
    //everything after '[' to the length read is the command.
    if (incomingData[0] != '[') {
       Serial.print("[!Badly formatted command]");  //! to indicate text string
       return -1; //skip the rest
    }
  
    //switch based on first character after the '['
      switch(incomingData[1]) {
        
        case '?':
         Serial.print("[MyArduino_1234567890]");
        break;
        
        case 'v':
         Serial.print('[');
         Serial.print(analogRead(temt6000Pin));
         Serial.print(']');     
         break;
         
       // Toggle continuous data.  
       case 's':
         if(!stream)
           stream = true;
         else
           stream = false;
         break;
         
        default:
          Serial.print("[!No matching command]");
      }

}
