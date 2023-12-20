
#include "SD.h"
//defines which pin is used to connect the SD card
#define SD_ChipSelectPin 8
#include "TMRpcm.h"
#include "SPI.h"

TMRpcm tmrpcm;
//set observed values from sensor when totally wet or totally dry as 0% or 100%
const int dry = 810; // value for dry sensor
const int wet = 395; // value for wet sensor

void setup(){
//defines pin where the speaker is connected
tmrpcm.speakerPin = 9;

Serial.begin(9600);

//trys to read the SD card
if (!SD.begin(SD_ChipSelectPin)) {
Serial.println("SD fail");
return;
}
tmrpcm.setVolume(4);
tmrpcm.play("2.wav");
delay(50000);
}

void loop(){  
  //read the humidity level from the sensor
  int sensorVal = analogRead(A0);
  int percentageHumidity = map(sensorVal, wet, dry, 100, 0); 
  Serial.print(percentageHumidity);
  Serial.println("%");

  // if the moisture level falls below 10% make the plant play a noise
  if (percentageHumidity < 10){
    tmrpcm.setVolume(5);
    tmrpcm.play("4.wav");
    delay(50000);
  }
  
  //Serial.println(sensorVal);
  delay(10000);
}


