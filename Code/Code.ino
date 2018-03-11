#include "HX711.h"

#define DOUT  3
#define CLK  2

#define PHONE 8
#define CHAPSTICK 9

HX711 scale(DOUT, CLK);
float calibration_factor = -186450.00; //-7050 worked for my 440lb max scale setup

void setup() {
  Serial.begin(9600);
  scale.set_scale();
  scale.tare();	//Reset the scale to 0

  pinMode(PHONE,OUTPUT);
  pinMode(CHAPSTICK,OUTPUT);
}

void loop() {

  scale.set_scale(calibration_factor); //Adjust to this calibration factor
//
//  Serial.print("Reading: ");
//  Serial.println(abs(scale.get_units()));
//  Serial.print(" lbs"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
  
  float weight = round(abs(scale.get_units())*100);
        weight /= 100;
  
  Serial.println(weight);
  if(weight == .39){
    digitalWrite(PHONE,HIGH);
    digitalWrite(CHAPSTICK,LOW);
    Serial.println("ON");
  }else if(weight == .02){
    digitalWrite(CHAPSTICK,HIGH);
    digitalWrite(PHONE,LOW); 
  }else{
    digitalWrite(PHONE,LOW); 
    digitalWrite(CHAPSTICK,LOW); 
  }
  delay(10);

  
}
