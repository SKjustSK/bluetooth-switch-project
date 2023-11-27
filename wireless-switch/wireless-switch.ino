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

// TEMP, all recieved_serial mentions are for test purposes, to use be used on serial monitor
String recieved_serial;

int switches[num_of_switches] = { 10 , 9 , 8 };

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
    // Recieving data in String format  
    recieved = communicator.readString();

    // TEST to use using Serial Monitor
    recieved_serial = Serial.readString();

    // To avoid random complications
    if (recieved != NULL || recieved_serial != NULL)
    {
        // Loop to turn on switch based on information recieved, ex. 101 recieved, then switch 1 OFF, switch 2 ON, switch 3 OFF
        // HW-316 relay module uses INVERSE LOGIC
        for (int i = 0 ; i < num_of_switches ; i++)
        {
            if (recieved[i] == '0' || recieved_serial[i] == '0')
            {
                // Turns ON
                digitalWrite(switches[i], HIGH);
            }
            else if (recieved[i] == '1' || recieved_serial[i] == '1')
            {
                // Turns OFF
                digitalWrite(switches[i], LOW);
            }
        }
    }
}