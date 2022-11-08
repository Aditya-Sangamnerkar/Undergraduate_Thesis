#include<stdlib.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

// global variables for nrf
RF24 radio(9, 10); // CE, CSN
uint8_t address[6]= "2Node";

// global variables for ultrasonic sensor
const int pingPin = 7; 
const int echoPin = 6;  

// global variables for servo
Servo myservo;
int pos = 0; 
float values[3] = {0,0,0};
float wt_avg;

int payload_length(int fillLevel);
char* declare_initialize_payload(int len);
long weighted_average();
long distance_calculation(long microseconds);


void setup()
{
    Serial.begin(19200);
    radio.begin(); 
    radio.setPALevel(RF24_PA_MIN);   
    myservo.attach(3);  
}

void loop()
{
    // get the fill level
    int fillLevel = (int)weighted_average();

    // get the number of digits in the fill level
    int data_len = data_length(fillLevel);

    // initialize the payload length
    int payload_len = payload_length(data_len);

    // declare and define the payload
    char *payload = (char*)malloc(payload_len);
    
    // initialize the payload
    payload[0] = '*';
    payload[1] = 'A';
    payload[payload_len - 2] = '#';
    payload[payload_len - 1] = '\0';

    for(int i=2; i<data_len+2; i++){
        payload[i] = '0';
    }
    
    // data_packet(payload, len, fillLevel);
    printf("%s",payload);
    free(payload);

    
}


int data_length(int fillLevel)
{ 
  int len = 0;
  // count number of digits in fillLevel
  while(fillLevel > 0)
  {
    fillLevel = fillLevel/10;
    len++; 
  }
  return len;
}

int payload_length(int data_length)
{
  // 1 byte each for start, stop, null and node identifier
  return data_length + 4;
}

void data_packet(char *payload, int len, int fillLevel)
{
  
   int fillLevelCopy = fillLevel;
   int i, digit;
   for(i=0;i<len;i++)
   {
      digit = fillLevelCopy % 10;
      switch(digit)
      {
            case 0:
                    payload[len-i-1] = '0';
                    break;
            case 1:
                    payload[len-i-1] = '1';
                    break;
            case 2:
                    payload[len-i-1] = '2';
                    break;
            case 3:
                    payload[len-i-1] = '3';
                    break;
            case 4:
                    payload[len-i-1] = '4';
                    break;
            case 5:
                    payload[len-i-1] = '5';
                    break;
            case 6:
                    payload[len-i-1] = '6';
                    break;
             case 7:
                    payload[len-i-1] = '7';
                    break;

             case 8:
                    payload[len-i-1] = '8';
                    break;
             case 9:
                    payload[len-i-1] = '9';
                    break;
      }
      fillLevelCopy = fillLevelCopy / 10;
   }
}


long distance_calculation(long microseconds) {
   return microseconds / 29 / 2;
}

long weighted_average()
{
  
   int i = 0;
   long duration, cm; 
   for (pos = 0; pos <= 180; pos += 1) { 
   
          myservo.write(pos);             
          delay(15);
          if(pos%90== 0)
          { 
     
              delay(5000);
              pinMode(pingPin, OUTPUT);
              digitalWrite(pingPin, LOW);
              delayMicroseconds(2);
              digitalWrite(pingPin, HIGH);
              delayMicroseconds(10);
              digitalWrite(pingPin, LOW);
              pinMode(echoPin, INPUT);
              duration = pulseIn(echoPin, HIGH);
              cm = distance_calculation(duration);
     
            values[i] = float(cm);
            i++;
            if(i == 2)
            {
                wt_avg = (values[0]+values[1]+values[2])/3;
            }      
        }
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
  }
  
  return wt_avg;
}
