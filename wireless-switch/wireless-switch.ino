/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.11 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.11.4 or later version;
     - for iOS 1.9.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// you can enable debug logging to Serial at 115200
//#define REMOTEXY__DEBUGLOG  

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL_RX 2
#define REMOTEXY_SERIAL_TX 3
#define REMOTEXY_SERIAL_SPEED 9600


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 74 bytes
  { 255,4,0,0,0,67,0,16,24,1,2,0,5,25,22,11,162,26,31,31,
  49,0,79,70,70,0,2,0,36,59,22,11,162,26,31,31,52,0,79,70,
  70,0,2,0,5,59,22,11,162,26,31,31,51,0,79,70,70,0,2,0,
  36,25,22,11,162,26,31,31,50,0,79,70,70,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 
  uint8_t switch_4; // =1 if switch ON and =0 if OFF 
  uint8_t switch_3; // =1 if switch ON and =0 if OFF 
  uint8_t switch_2; // =1 if switch ON and =0 if OFF 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)


/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////


#define num_of_switches 4

int switches[num_of_switches] = { 10 , 9 , 8 };

// INVERSE LOGIC RELAY
const uint8_t ON = 0;
const uint8_t OFF = 1;

void setup() 
{
    RemoteXY_Init (); 

    // Setup Code
    for (int i = 0 ; i < num_of_switches ; i++)
    {
        pinMode(switches[i], OUTPUT);
    }
    Serial.begin(9600);
}


void loop() 
{ 
    RemoteXY_Handler ();

    uint8_t recieved[num_of_switches] = {
        RemoteXY.switch_1, 
        RemoteXY.switch_2, 
        RemoteXY.switch_3, 
        RemoteXY.switch_4
    };

    // use the RemoteXY structure for data transfer
    // do not call delay(), use instead RemoteXY_delay() 

    // Main Logic
    for (int i = 0 ; i < num_of_switches ; i++)
    {   
        if (recieved[i] == OFF)
        {
            digitalWrite(switches[i], LOW); 
        }
        else if (recieved[i] == ON)
        {
            digitalWrite(switches[i], HIGH);
        }
    }
}