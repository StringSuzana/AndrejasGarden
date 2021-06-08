
/**
 * @file AndrejasGarden.cpp
 * @author StringSuzana
 * @brief
 * @version 1.0
 * @date 2021-06-08
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "config.h"

int pumpPin_1 = 12;
int pumpPin_2 = 13;
int pumpPin_3 = 15;

bool pump1_is_on = false;
bool pump2_is_on = false;
bool pump3_is_on = false;

#define INTERVAL_PUMP1 10000
#define INTERVAL_PUMP2 20000
#define INTERVAL_PUMP3 30000

unsigned long time_1 = 0;
unsigned long time_2 = 0;
unsigned long time_3 = 0;
int count = 0;

#define IO_LOOP_DELAY 15000
unsigned long lastUpdate = 0;

AdafruitIO_Feed *pump1 = io.feed("pumpa1");
AdafruitIO_Feed *pump2 = io.feed("pumpa2");
AdafruitIO_Feed *pump3 = io.feed("pumpa3");

void setup() {
  pinMode(pumpPin_1, OUTPUT);
  pinMode(pumpPin_2, OUTPUT);
  pinMode(pumpPin_3, OUTPUT);

  Serial.begin(115200);
  while(! Serial);
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  pump1->onMessage(handlePump1);
   pump2->onMessage(handlePump2);
    pump3->onMessage(handlePump3);

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());

  pump1->get();
  pump2->get();
  pump3->get();
}

void loop() {
  io.run();

  if(millis() >= (time_1 + INTERVAL_PUMP1) && pump1_is_on==true){
   digitalWrite(pumpPin_1, LOW);
   pump1->save("OFF");
   pump1_is_on=false;
   }
  if(millis() >= (time_2 + INTERVAL_PUMP1) && pump2_is_on==true){
   digitalWrite(pumpPin_2, LOW);
   pump2->save("OFF");
   pump2_is_on=false;
   }
  if(millis() >= (time_3 + INTERVAL_PUMP1) && pump3_is_on==true){
   digitalWrite(pumpPin_3, LOW);
   pump3->save("OFF");
   pump3_is_on=false;
   }
}
void handlePump1(AdafruitIO_Data *data) {
  String valueData = data->value();

  if(valueData == "ON")
  {
         time_1=millis();
         digitalWrite(pumpPin_1, HIGH);
         pump1_is_on=true;
  }
  if(valueData == "OFF" && pump1_is_on== true)
  {
         digitalWrite(pumpPin_1, LOW);
         pump1->save("OFF");
         pump1_is_on=false;
  }
}
void handlePump2(AdafruitIO_Data *data) {
    String valueData = data->value();

  if(valueData == "ON")
  {
         time_2=millis();
         digitalWrite(pumpPin_2, HIGH);
         pump2_is_on=true;
  }
  if(valueData == "OFF" && pump2_is_on== true)
  {
         digitalWrite(pumpPin_2, LOW);
         pump2->save("OFF");
         pump2_is_on=false;
  }

}
void handlePump3(AdafruitIO_Data *data) {

String valueData = data->value();

  if(valueData == "ON")
  {
         time_3=millis();
         digitalWrite(pumpPin_3, HIGH);
         pump3_is_on=true;
  }
  if(valueData == "OFF" && pump3_is_on== true)
  {
         digitalWrite(pumpPin_3, LOW);
         pump3->save("OFF");
         pump3_is_on=false;
  }
}
