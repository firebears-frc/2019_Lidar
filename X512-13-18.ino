#include <Wire.h>
#include "Adafruit_VL53L0X.h"
#define TCAADDR 0x70
//#define LOX1_ADDRESS 0x29

//Adafruit_VL53L0X lox = Adafruit_VL53L0X();
//Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
/*Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();
  Adafruit_VL53L0X lox4 = Adafruit_VL53L0X();
  Adafruit_VL53L0X lox5 = Adafruit_VL53L0X();*/

VL53L0X_RangingMeasurementData_t measure[5];

float Distances[5];

Adafruit_VL53L0X lox[5];


/*VL53L0X_RangingMeasurementData_t measure1;
  VL53L0X_RangingMeasurementData_t measure2;
  VL53L0X_RangingMeasurementData_t measure3;
  VL53L0X_RangingMeasurementData_t measure4;
  VL53L0X_RangingMeasurementData_t measure5;*/

int PINS[] = {
  7, 6, 5, 4, 3
};

void tcaselect(uint8_t i) {
  if (i > 7) return;

  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);

  Wire.endTransmission();
}
void setup() {
  Serial.begin(19200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(10);

  }
  Serial.println("Lidar Array Test...");
  Serial.println("");
  /* pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);*/
  for (int i = 0; i < 5; i++) {
    pinMode(PINS[i], OUTPUT);
  }

  tcaselect(0); //select Lidar 1
  delay(10);
  /* if(!lox[0].begin()) {
      Serial.println(F("Failed to boot VL53L0X 0"));
      while(1);
    }*/
  !lox[0].begin();
  delay(10);


  tcaselect(1); //select Lidar 2
  /* delay(10);
    if(!lox[1].begin()) {
     Serial.println(F("Failed to boot VL53L0X  1"));
     while(1);
    }*/
  delay(10);
  !lox[1].begin();
  delay(10);

  tcaselect(2); //selects Lidar 3
  /* if(!lox[2].begin()) {
     Serial.println(F("Failed to boot VL53L0X  2"));
     while(1);
    }*/
  !lox[2].begin();
  delay(10);

  tcaselect(3); //selects Lidar 4
  /* if(!lox[3].begin()) {
     Serial.println(F("Failed to boot  VL53L0X  3"));
     while(1);
    }*/
  !lox[3].begin();
  delay(10);


  tcaselect(4); //selects Lidar 5
  /*if(!lox[4].begin()) {
    Serial.println(F("Failed to boot  VL53L0X  4"));
    while(1);
    }*/
  !lox[4].begin();
  delay(10);
}



void loop() {
  float Distances[5];
  int minLight = 0;

  float minDistance = 2500.0;
  
  for (int i = 0; i < 5; i++ )  {
    VL53L0X_RangingMeasurementData_t measure[i];
    tcaselect(i);  //connects to Lidar 1
    lox[i].rangingTest(&measure[i], false);


    if (measure[i].RangeStatus == 4) {
      Distances[i] = 2000.0;
      if (Distances[i] < minDistance) {
        minDistance = Distances[i];
        minLight = i;
      }
      //Serial.print(" Status = 4  ");
    }

    else {  // phase failures have incorrect data

      Distances[i] = measure[i].RangeMilliMeter;

      if (Distances[i] < minDistance) {
        minDistance = Distances[i];
        minLight = i;
      }
      //Serial.print(" Status = 0  ");

    }
    Serial.print(i);
    Serial.print("   ");
    Serial.println(Distances[i]);
    delay(10);
  }

  Serial.print("Min Distance: = ");
  Serial.print(minDistance);
  Serial.print("    Lidar no :  ");
  Serial.println(minLight);

  for (int i = 0; i < 5; i++ )  {
    if (i == minLight && minDistance < 1000.0) {
      digitalWrite(PINS[i], HIGH);
    }
    else {
      digitalWrite(PINS[i], LOW);
    }
  }
  delay(10);
}



// int AVG = (Distances[0] + Distances[1] + Distances[2] + Distances[3] + Distances[4]) / 5;
// Serial.print("Average: ");
// Serial.println(AVG);

// int ClosetDistances = 500;
// int ClosestIndex;


// for (int i = 0; i < 5; i++) {
//   if (Distances[i] < ClosetDistances) {
//     ClosetDistances = Distances[i];
//   }

// }
//  Serial.print(ClosetDistances);


//  delay(1000);


//}
