#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
uint8_t addresses[][6] = {"1Node","2Node"};

uint8_t pipe1 = 1;
uint8_t pipe2 = 2;
char data1[32] ;
char data2[32] ;





void setup()
{
    
    Serial.begin(9600);
    radio.begin();
    radio.setPALevel(RF24_PA_MIN);   
    radio.openReadingPipe(1,addresses[0]);
    radio.openReadingPipe(2,addresses[1]);
    radio.startListening();
  
  
 }



void loop()
{
      

     int i;
     for(i=0;i<2;i++)
     {    

             switch(i)
             {
                case 0:
                         if(radio.available(&pipe1)){
                                radio.read(&data1,sizeof(data1));
                                Serial.print("Got data on pipe ");
                               // Serial.println(pipe1);
                                Serial.println(data1);
                                }

                                
                             break;

              
             


              case 1:      if(radio.available(&pipe2)){
                          radio.read(&data2,sizeof(data2));
                              Serial.print("Got data on pipe ");
                              //.println(pipe2);
                              Serial.println(data2);}
                              break;
                        

        }
      
      
      }
         
}
