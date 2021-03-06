#include <Encoder.h>
#include <Wire.h>
#include <HID-Project.h>
#include "paj7620.h"

#define GES_REACTION_TIME    300
#define GES_ENTRY_TIME      400 
#define GES_QUIT_TIME     400

void setup()
{
  uint8_t error = 0;

  Serial.begin(9600);
  error = paj7620Init();
  if (error) 
  {
    Serial.print("INIT ERROR,CODE:");
    Serial.println(error);
  }
  else
  {
    Serial.println("INIT OK");
  }
  Serial.println("Start Controlling Media with Gesturesn");
}

void loop()
{
  uint8_t data = 0, data1 = 0, error;
  
  error = paj7620ReadReg(0x43, 1, &data); 
  if (!error) 
  {
    switch (data)   
    {
      case GES_RIGHT_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Mute/No Mute");
          Consumer.write(MEDIA_VOLUME_MUTE);
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Mute/No Mute");
          Consumer.write(MEDIA_VOLUME_MUTE);
          delay(GES_QUIT_TIME);
        }
        else
        {

          Serial.println("Previous");
          Consumer.write(MEDIA_PREVIOUS);
          delay(500);
        }          
        break;
      case GES_LEFT_FLAG: 
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Mute/No Mute");
          Consumer.write(MEDIA_VOLUME_MUTE);
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Mute/No Mute");
         Consumer.write(MEDIA_VOLUME_MUTE);
          delay(GES_QUIT_TIME);
        }
        else
        {
         Serial.println("Next");
         Consumer.write(MEDIA_NEXT);
         delay(500);
        }          
        break;
      case GES_UP_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Mute/No Mute");
          Consumer.write(MEDIA_VOLUME_MUTE);
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
        Serial.println("Mute/No Mute");
        Consumer.write(MEDIA_VOLUME_MUTE);
        delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Nothing Assigned");
        }          
        break;
      case GES_DOWN_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Mute/No Mute");
          Consumer.write(MEDIA_VOLUME_MUTE);
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Mute/No Mute");
         Consumer.write(MEDIA_VOLUME_MUTE);
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Nothing Assigned");
        }          
        break;
      case GES_FORWARD_FLAG:
        Serial.println("Mute/No Mute");
        Consumer.write(MEDIA_VOLUME_MUTE);
        delay(GES_QUIT_TIME);
        break;
      case GES_BACKWARD_FLAG:     
        Serial.println("Mute/No Mute");
       Consumer.write(MEDIA_VOLUME_MUTE);
        delay(GES_QUIT_TIME);
        break;
      case GES_CLOCKWISE_FLAG:
        Serial.println("Volume Up");
        Consumer.write(MEDIA_VOLUME_UP);
        delay(100);
        break;
      case GES_COUNT_CLOCKWISE_FLAG:
        Serial.println("Volume Down");
       Consumer.write(MEDIA_VOLUME_DOWN);
       delay(100);

        break;  
      default:
        paj7620ReadReg(0x44, 1, &data1);
        if (data1 == GES_WAVE_FLAG) 
        {
          Serial.println("Nothing Assigned");
        }
        break;
    }
  }
  delay(100);
}
