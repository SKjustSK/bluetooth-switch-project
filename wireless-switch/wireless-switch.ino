// Bluetooth controlled switches
// Sending string '101' turns on first and thrid switch. Change only num_of_switches to increase switches.

// Turning ON and OFF at start of circuit
// Present issue: Large amount of Delay

#include <SoftwareSerial.h>

// Defining pins
#define num_of_switches 3
#define rxPin 2
#define txPin 3

SoftwareSerial communicator(rxPin, txPin);

String recieved;

// TO REMOVE
String recieved_serial;

int switches[num_of_switches] = { 10 , 9 , 8 };

// Last digit = ON/OFF
// Previous digits -> Switch number
const String switch_ID[2][num_of_switches] = {
    {"10","20","30"}, // OFF
    {"11","21","31"} // ON
};

void setup()
{
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);
    for (int i = 0 ; i < num_of_switches ; i++)
    {
        pinMode(switches[i], OUTPUT);
    }
    Serial.begin(9600);
    communicator.begin(9600);
}

void loop()
{
    recieved = communicator.readString();
    recieved.trim();

    // TO REMOVE
    recieved_serial = Serial.readString();
    recieved_serial.trim();
    
    // Main Logic
    if (recieved != NULL || recieved_serial != NULL) // To avoid random complications
    {
        Serial.println(recieved);
        
        for (int i = 0 ; i < num_of_switches ; i++) 
        {   
            // HW-316 relay module uses INVERSE LOGIC
            if (recieved.equals(switch_ID[0][i]) || recieved_serial.equals(switch_ID[0][i]))
            {
                digitalWrite(switches[i], HIGH); // Turns OFF
            }
            else if (recieved.equals(switch_ID[1][i]) || recieved_serial.equals(switch_ID[1][i]))
            {
               
                digitalWrite(switches[i], LOW); // Turns ON
            }
        }
    }
}