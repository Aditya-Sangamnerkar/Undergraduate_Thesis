
#include<stdlib.h>
int payload_length(int fillLevel);
char* declare_initialize_payload(int len);


 void setup()
 {
     Serial.begin(19200);
 }

void loop()
{
    // get the fill level
    int fillLevel = (int)145.67;

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
    
    data_packet(payload, 2, data_len+2, fillLevel);
//    printf("%s",payload);
    Serial.println(payload);
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

void data_packet(char *payload, int start, int end, int fillLevel)
{
  
   int fillLevelCopy = fillLevel;
   int i, digit;
   for(i=start;i<end;i++)
   {
      digit = fillLevelCopy % 10;
      switch(digit)
      {
            case 0:
                    payload[end+start-i-1] = '0';
                    break;
            case 1:
                    payload[end+start-i-1] = '1';
                    break;
            case 2:
                    payload[end+start-i-1] = '2';
                    break;
            case 3:
                    payload[end+start-i-1] = '3';
                    break;
            case 4:
                    payload[end+start-i-1] = '4';
                    break;
            case 5:
                    payload[end+start-i-1] = '5';
                    break;
            case 6:
                    payload[end+start-i-1] = '6';
                    break;
             case 7:
                    payload[end+start-i-1] = '7';
                    break;

             case 8:
                    payload[end+start-i-1] = '8';
                    break;
             case 9:
                    payload[end+start-i-1] = '9';
                    break;
      }
      fillLevelCopy = fillLevelCopy / 10;
   }
}


