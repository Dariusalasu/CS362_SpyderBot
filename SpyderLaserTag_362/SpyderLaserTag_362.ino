/* Spyder Control
 *  
 *  Last Edited: 12/2/2019
 *  
 *  Created By:
 *    Darius Alasu
 *    NetID: Dalasu2
 *    UIN: 664323974
 *  
 *  In partnership with:
 *    Adrian Wheeler
 *    NetID: Alwhelr2
 *    UIN: ----------
 *  
 *  The Spyder Control is the code which controls the spyder body. This includes the following:
 *    - 2 Spider body kits
 *    - 1 Infrared Reciever
 *    - 2 Motors
 *    - 1 Buzzer
 *    - 2 Battery packs (a third can be added to hold arduino power supply)
 *    - Elegoo Uno R3 board
 *    - Prototype expansion board
 *    - Small breadboard
 *    - Wires
 *  
 *  The SLT-Bot (Spyder Laser Tag Robot) is designed with three distinct functions: A user
 *  controlled state, an idle state, and a laser tag state. In the user controlled state, the
 *  user can control the spyder using a remote control. In the idle state, the spyder is powered
 *  on but is not controlled, idling and exploring the environment. In the laser tag state, the
 *  user can fire an infrared light at the spyder using the controller as it runs away trying to
 *  avoid the shots. These three functions allow for a companion which the user can engage with
 *  in multiple ways.
 *  
 *  Assumptions:
 *    - We assume that the inputs will not interfere with each other
 *    - We assume that while any foreign infrared signal may be read, the spider operates correctly
 *    - We assume that the parts used are reliable and will not faulter during any demonstration
 *  
 *  References:
 *  https://www.instructables.com/id/Using-Motors-With-L293D-IC/
 *  http://www.robotplatform.com/howto/L293/motor_driver_1.html
 *  https://create.arduino.cc/projecthub/GeneralSpud/passive-buzzer-song-take-on-me-by-a-ha-0f04a8
 *  https://www.pjrc.com/teensy/td_libs_IRremote.html
 *  https://arduino.stackexchange.com/questions/67239/tone-conflicts-with-irremote-library-multiple-definition-of-vector-7
 *  
 */

#ifndef VECDEFS
#define VECDEFS
#define __vector_7
#define CE_PIN 8
#define CSN_PIN 10
#endif

#include <IRremote.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include "pitches.h"
#include "sounds.h"

//Pins
const int motorPinR1 = 2;
const int motorPinR2 = 3;
const int motorPinL1 = 4;
const int motorPinL2 = 5;
const int IRSensor = 6;
const int buzzer = 7;

IRrecv irrecv(IRSensor);
decode_results results;
RF24 radio(CE_PIN, CSN_PIN);
const uint64_t pipe = 0xE8E8F0F0E1LL;

//Variables
String command; //String to hold command received from controller
int lives;  //Lives for laser tag
int idleNum;  //Number for switch cases to decide what robot should do while idling
long idleTime;  //Time which robot should remain idled
unsigned long prevIdle; //Time from previous idle command
bool idle = false;

//setup:
//Initialize all variables/pins/inputs/outputs
void setup() {
  Serial.begin(9600);
  
  //Set up IR receiver
  irrecv.enableIRIn();

  //Set up radio receiver
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.setChannel(115);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
  
  //Pin setup
  pinMode(motorPinR1, OUTPUT);
  pinMode(motorPinR2, OUTPUT);
  pinMode(motorPinL1, OUTPUT);
  pinMode(motorPinL2, OUTPUT);
  pinMode(buzzer, OUTPUT);

  //Set up variables
  lives = 3;
  idleNum = 6;
  prevIdle = millis();
  idleTime = 0;

  playSound(startup, startup_D, sizeof(startup)/sizeof(startup[0])); //Play startup sound
}//End of setup

//loop:
//Perform repeating loop receiving data from sensors
//Calls other functions to perform other actions depending on data
void loop() {
  //Right Motor (R):
  //  R1 - HIGH, R2 - LOW: Backwards
  //  R1 - LOW, R2 - HIGH: Forwards
  //Left Motor (L):
  //  L1 - HIGH, L2 - LOW: Backwards
  //  L1 - LOW, L2 - HIGH: Forwards

  String msg = "";
  bool rcControl;
  //Main loop for remote control:
  //Read serial data from serial monitor
  //Save command and update boolean values
  //Execute respective command based on data received
  
  if (!idle)
  {
    if(radio.available()) 
    {
      //playSound(startup, startup_D, sizeof(startup)/sizeof(startup[0]));
      char data[20] = "";
      radio.read(data, sizeof(data));
      //Serial.println(data);
      command = data;
      if (!command.equals("5"))
      {
        //Respond to input here 
        if (command.equals("1"))
        {
           Serial.println("Counterclockwise");
           motorControl(LOW, HIGH, HIGH, LOW);
        }
        else if (command.equals("2"))
        {
           Serial.println("Clockwise");
           motorControl(HIGH, LOW, LOW, HIGH);
        }
        //Move forward
        else if (command.equals("3"))
        { 
           Serial.println("Foward");
           motorControl(LOW, HIGH, LOW, HIGH);
        }
        //Move backward
        else if (command.equals("4"))
        {
           Serial.println("Backward");
           motorControl(HIGH, LOW, HIGH, LOW);
        } 
        //Turn the motors off
        else
        {
           Serial.println("Stop moving");
           motorControl(LOW, LOW, LOW, LOW);
        }
      }
      else
      {
        idle = true;
        Serial.println("Now idling...");
        motorControl(LOW, LOW, LOW, LOW);
      }
    } 
  }
  else {
    //Check if we need to switch back to player controlled
    if(radio.available()) 
    {
      char data[20] = "";
      radio.read(data, sizeof(data));
      command = data;
      if (command.equals("5"))
      {
        idle = false;
        Serial.println("Returning to player control...");
        motorControl(LOW, LOW, LOW, LOW);
        return;
      }
    } 
    int prevIdleNum; //Number for previous switch cases to make sure some stuff are not repeated

    //Idle portion:
    //If statement will check if time for idling has passed and will update the following accordingly:
    // ~ prevIdleNum
    // ~ idleNum
    // ~ idleTime
    // ~ prevIdle
    if(millis() - prevIdle >= idleTime) {
      motorControl(LOW, LOW, LOW, LOW);
      delay(300);
      prevIdleNum = idleNum;
      idleNum = getRandomCase(random(0, 30), prevIdleNum);
      idleTime = random(1, 4) * 1000;
      prevIdle = millis();
    }

    //Switch cases will decide what spyder does when idling
    switch(idleNum) {
      case 0: //Move forward
        motorControl(LOW, HIGH, LOW, HIGH);
        break;
      case 1: //Turn clockwise
        motorControl(HIGH, LOW, LOW, HIGH);
        break;
      case 2: //Turn counter-clockwise
        motorControl(LOW, HIGH, HIGH, LOW);
        break;
      case 3: //Do nothing
        motorControl(LOW, LOW, LOW, LOW);
        break;
      case 4: //Play curious sound
        playSound(curious, curious_D, sizeof(curious)/sizeof(curious[0]));
        idleTime = 0;
        break;
      case 5: //Play song
        //Add dancing mechanic
        for(int i = 0; i < 2; i++) {
          playSound(takeMeOn, takeMeOn_D, sizeof(takeMeOn)/sizeof(takeMeOn[0]));
        }
        idleTime = 0;
        break;
      case 6: //Play song
        playSound(Annie_Melody, Annie_Melody_D, sizeof(Annie_Melody)/sizeof(Annie_Melody[0]));
        idleTime = 0;
        break;
    }//End of switch cases

    //Laser tag portion:
    //If the infrared sensor receives a signal, the laser hit the spyder
    if(irrecv.decode(&results)) {
      delay(10);
      //Check to make sure data is actually received and no foreign objects are interfering
      if(sizeof(results) > 0) {
        //Make sound to imitate robot shock
        playSound(surprised, surprised_D, sizeof(surprised)/sizeof(surprised[0]));
        //Call panic function to allow robot to run around in panic
        panic();
        //Reset lives to 3
        lives = 3;
      }
      irrecv.resume(); //Receive the next value
    }//End of laser tag portion
    
  }//End of if-else
  
}//End of loop

//Generate hash code for random number to perform certain action
// ~ 0: Move forward
// ~ 1: Turn right
// ~ 2: Turn left
// ~ 3: Do nothing
// ~ 4: Play curious sound effect
// ~ 5: Play takeMeOn song and dance
// ~ 6: Play Annie's song
int getRandomCase(int num, int prevN) {
  if(num < 6) {
    return 0; //Move forward
  } else if(num < 11) {
    //If statement to prevent robot from turning one way and then instantly turning the other way
    if(prevN == 2) {
      return 0; //Move forward
    }
    return 1; //Turn right
  } else if(num < 16) {
    //If statement to prevent robot from turning one way and then instantly turning the other way
    if(prevN == 1) {
      return 0; //Move forward
    }
    return 2; //Turn left
  } else if(num < 26) {
    return 3; //Do nothing (stop motors)
  } else if(num < 28) {
    //If statement to stop robot from making same sound twice in a row
    if(prevN == 4) {
      return 3; //Do nothing
    }
    return 4; //Play curious sound
  } else if(num == 28) {
    //If statement to stop robot from singing same song twice in a row
    if(prevN == 5) {
      return 3; //Do nothing
    }
    return 5; //Play takeMeOn
  } else if(num == 29) {
    //If statement to stop robot from singing same song twice in a row
    if(prevN == 6) {
      return 3; //Do nothing
    }
    return 6; //Play Annie's song
  } else {
    return 3; //Error so do nothing
  }
}//End of getRandomCase

//panic:
//Called when spyder first detects an infrared signal for the first time
//Uses millis to time the frequency of infrared detection:
// ~ if does not detect infrared within 5 seconds, return to idling state
// ~ if detects infrared within 5 seconds, call laserHit respond accordingly:
//    ~ if lives is <= 0, reset lives and return to idling state
//    ~ if lives is > 0, update prevTime and resume to detect next infrared
void panic() {
  irrecv.resume(); //Receive the next value
  long idle = 5000; //5 seconds before returning to idling state
  unsigned long prevTime = millis(); //Set prevTime to current time

  //Loop to perform panic routine
  while(true) {
    //Runs forward to get away from situation
    motorControl(LOW, HIGH, LOW, HIGH);

    //Check if robot has not detected hit in over 5 seconds and reset to normal actions if not hit
    if(millis() - prevTime >= idle) {
      motorControl(LOW, LOW, LOW, LOW); //Stop spyder from moving
      playSound(haha, haha_D, sizeof(haha)/sizeof(haha[0])); //Play haha sound
      return;
    }

    //If spyder detects an infrared signal, indicate spyder has been hit
    if(irrecv.decode(&results)) {
      //Call laserHit to indicate robot has been hit
      laserHit();
      //Check if lives is <= 0 and return to idling state if it is
      if(lives <= 0) {
        return;
      }
      prevTime = millis(); //Set prevTime to current time
      irrecv.resume(); // Receive the next value
    }
    delay(10);
  }//End of while loop
}//End of panic

//laserHit:
//Called when infrared sensor detects a signal
//Stops spyder, updates lives, and performs respective action (plays sound)
void laserHit() {
  lives--;  //Decrease lives
  motorControl(LOW, LOW, LOW, LOW); //Stop spyder

  if(lives <= 0) {  //If lives is 0 or less
    //Play "highToLow" sound
    playSound(highToLow, highToLow_D, sizeof(highToLow)/sizeof(highToLow[0])); //Play death sound
    delay(1000);
  } else {  //If lives is greater than 0
    //Play tone to indicate hit
    int pause = 1000*1.3; //Pause between notes
    tone(buzzer, NOTE_B2, 1500);
    delay(pause);
    noTone(buzzer);
  }
  
  delay(1000);
}//End of laserHit

//playSound:
//Function that takes in two arrays and a size
//Uses first int array to determine notes to play
//Uses second double array to determine duration of notes
//Uses size to determine how many notes to play
void playSound(int notes[], double dur[], int sL) {
  //Loop through each note and play tone
  for (int thisNote = 0; thisNote < sL; thisNote++){
    //Determine the duration of the notes that the computer understands
    int duration = (int)(1000/ dur[thisNote]);
    tone(buzzer, notes[thisNote], duration); //Play tone
    int pause = duration * 1.3; //Pause between notes
    delay(pause);
    noTone(buzzer); //Stope the tone
  }
}//End of playSound

//motorControl:
//Function to control motor motion by writing each pin with the respective value
//Does nothing if the two values from same motor are HIGH to avoid destroying the motor/arduino
void motorControl(int r1, int r2, int l1, int l2) {
  //Return if both values from one motor are HIGH
  //Safety measure to not damage arduino/motors
  if((r1 > 0 && r2 > 0) || (l1 > 0 && l2 > 0)) {
    Serial.println("ERROR: INVALID PIN VALUES");
    return;
  }
  //Write values to each pin
  digitalWrite(motorPinR1, r1);
  digitalWrite(motorPinR2, r2);
  digitalWrite(motorPinL1, l1);
  digitalWrite(motorPinL2, l2);
}//End of motorControl
