#include <Arduino.h>
#include <ArduinoJson.h>

DynamicJsonDocument doc(1024);
#define buttons_count 9

boolean state_buttons[buttons_count];

boolean flag_change = 0;
byte addr_arduino = 9;

void setup()
{
  doc["placement"] = addr_arduino;
  Serial.begin(9600);
  for (int i = 2; i <= buttons_count + 1; i++)
  {
    pinMode(i, INPUT_PULLUP);
  }
}

void read_buttons()
{

  for (int i = 0; i < buttons_count; i++)
  {
    state_buttons[i] = digitalRead(i + 2);
  }

}

void loop()
{
  read_buttons();
  if (Serial.available() != 0)
  {
    if (Serial.read() == 'S')
    {
      //Serial.print(addr_arduino); 
      for (int i = 0; i < buttons_count; i++)
      {

        //Serial.print(state_buttons[i]);
        doc["data"][i]["key"]=i+1;
        doc["data"][i]["status"]=state_buttons[i];
      }
      serializeJson(doc, Serial);
      Serial.println();
    }
    else Serial.read(); 
  }
}

