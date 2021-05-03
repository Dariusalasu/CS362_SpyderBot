//Arduino Joystick shield Code
#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>


#define CE_PIN  9
#define CSN_PIN 10

int up_button     = 2; // A
int down_button   = 4; // C 
int left_button   = 5; // D 
int right_button  = 3; // B
int start_button  = 6; // F
int select_button = 7; // E
int analog_button = 8; // 
int x_axis = A0;
int y_axis = A1;
int buttons[]={up_button, down_button,left_button,
               right_button,start_button,select_button,analog_button};
int ledPin = 8, ledState = 0;
int oldX, oldY, cX, cY, oldB, cB, oldF, cF;
bool turning = false, moving = false;;


const byte pipe[6] = {'R', 'x', 'A', 'A', 'A', 'B'};
RF24 radio(CE_PIN,CSN_PIN);
char msg[20] = "";

void setup()
{
     for(int i; i <7 ; i++)
     {
         pinMode(buttons[i],INPUT);
         digitalWrite(buttons[i],HIGH);  
     } 
     Serial.begin(9600);
     radio.begin();
     radio.setChannel(110);
     radio.setDataRate( RF24_250KBPS );
     radio.openWritingPipe(pipe);
     //radio.stopListening();
     pinMode(ledPin, OUTPUT);
     digitalWrite(ledPin, ledState);
     oldX = analogRead(x_axis);
     oldY = analogRead(y_axis);
     oldB = digitalRead(down_button);
     oldF = digitalRead(right_button);
}

void loop()
{       
      if(digitalRead(up_button)==LOW)
      {
        Serial.println("Laser activated!");
        ledState = !ledState;
        delay(300);
        digitalWrite(ledPin, ledState);
      }
      cB = digitalRead(down_button);
       if(cB == LOW && oldB == HIGH && !turning)
       {
        char msg[0]="4";
        radio.write(&msg,sizeof(msg));
        Serial.println("Moving backward");
        moving = true;
      }
      else if (cB == HIGH && oldB == LOW && !turning)
      {
        char msg[0]="0";
        radio.write(&msg,sizeof(msg));
        Serial.println("Stop moving");
        moving = false;
      }
      oldB = cB;
       if(digitalRead(left_button)==LOW)
      {
        char msg[0]="5";
      radio.write(&msg,sizeof(msg));
      delay(300);
        Serial.println("Changing state");
      }
      cF = digitalRead(right_button);
       if(cF==LOW && oldF == HIGH && !turning)
       {
        char msg[0]="3";
      radio.write(&msg,sizeof(msg));
        Serial.println("Moving forward");
        moving = true;
      }
      else if (cF == HIGH && oldF == LOW && !turning)
      {
        char msg[0]="0";
        radio.write(&msg,sizeof(msg));
        Serial.println("Stop moving");
        moving = false;
      }
      oldF = cF;
      cX = analogRead(x_axis);
      cY = analogRead(y_axis);
      if (oldX >= 341 && cX < 341 && !moving)
      {
        //We have moved to the left
        char msg[]="1";
        radio.write(&msg,sizeof(msg));
        delay(300);
        Serial.println("Move counterclockwise"); 
        turning = true;
      }
      else if (oldX < 341 && cX >= 341 && !moving)
      {
        char msg[]="0";
        radio.write(&msg,sizeof(msg));
        delay(300);
        Serial.println("Stop moving");
        turning = false;
      }
      else if (oldX < 682 && cX >= 682 && !moving)
      {
        //We have moved to the right
        char msg[0]="2";
        radio.write(&msg,sizeof(msg));
        delay(300);
        Serial.println("Move clockwise");   
        turning = true;
      }
      else if (oldX >= 682 && cX < 682 && !moving)
      {
        char msg[0]="0";
        radio.write(&msg,sizeof(msg));
        delay(300);
        Serial.println("Stop moving");
        turning = false;
      }
      oldX = cX;
      oldY = cY;
}
