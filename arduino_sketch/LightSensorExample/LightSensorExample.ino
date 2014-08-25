/*
  Light sensor example.
*/

//int led = 13;
int tempt6000Pin = 0;
int numCharRead = 0;
char incomingData[20];

// the setup routine runs once when you press reset:
void setup() {                
    // initialize the digital pin as an output.
    //pinMode(led, OUTPUT);  
  
    //Setup the serial port
    Serial.begin(9600);
}

// Infinite loop to get user input:
void loop() {
    if (Serial.available() > 0) {
        numCharRead = Serial.readBytesUntil(']',  incomingData, 19);
        processCommands(numCharRead);        
    }
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
        
        // Return the device ID string.
        case '?':
            Serial.print("My_Arduino_1234567890]");
             break;
        
        // Return the sensor reading.
        case 'get':
            int value = analogRead(temt6000Pin);
            Serial.println(value);
            break;
        
        default:
            Serial.print("[!No matching command]");
    }
}
