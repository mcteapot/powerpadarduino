
/* 
NES POWERPAD to UNOJOY
By @CyborgDino
03 June 2013
LOS ANGELES, USA
*/


#include "UnoJoy.h"

/* INITIALISATION */

int latch = 2; // set the latch pin
int clock = 3; // set the clock pin
int data1 = 4; // set the data in pin
int data3 = 5;
int data4 = 6;

//byte controller_data1 = 0;
byte controller_data3 = 0;
byte controller_data4 = 0;


uint8_t pad01 = 0;
uint8_t pad02 = 0;
uint8_t pad03 = 0;
uint8_t pad04 = 0;
uint8_t pad05 = 0;
uint8_t pad06 = 0;
uint8_t pad07 = 0;
uint8_t pad08 = 0;
uint8_t pad09 = 0;
uint8_t pad10 = 0;
uint8_t pad11 = 0;
uint8_t pad12 = 0;



void setup() {
  //Serial.begin(9600);
  setupPins();
  setupUnoJoy();
}

void loop() {
  // Always be getting fresh data
  padRead();
  readPadBit();
  
  dataForController_t controllerData = getControllerData();
  setControllerData(controllerData);
  
  delay(100);
}

void setupPins(void){
  // pin setup
  //Serial.begin(57600);
  
  Serial.begin(9600);
  pinMode(latch,OUTPUT);
  pinMode(clock,OUTPUT);
  
  pinMode(data3,INPUT);
  pinMode(data4,INPUT);
  
  digitalWrite(latch,HIGH);
  digitalWrite(clock,HIGH);
}

void padRead() {
  //controller_data1 = 0;
  controller_data3 = 0;
  controller_data4 = 0;
  digitalWrite(latch,LOW);
  digitalWrite(clock,LOW);
  
  digitalWrite(latch,HIGH);
  delayMicroseconds(2);
  digitalWrite(latch,LOW);
  
  //controller_data1 = digitalRead(data1);
  controller_data3 = digitalRead(data3);
  controller_data4 = digitalRead(data4);
  
    
  for (int i = 1; i <= 7; i ++) {
    digitalWrite(clock,HIGH);
    delayMicroseconds(2);
    
    //Serial.println(i);
    
    //controller_data1 = controller_data1 << 1;
    //controller_data1 = controller_data1 + digitalRead(data1);

    controller_data3 = controller_data3 << 1;
    controller_data4 = controller_data4 << 1;
   
    controller_data3 = controller_data3 + digitalRead(data3);
    controller_data4 = controller_data4 + digitalRead(data4); 
    
 

    delayMicroseconds(4);
    digitalWrite(clock,LOW);
  }
  
}

void readPadBit() {
  byte controller_not_data3 = ~controller_data3;
  byte controller_not_data4 = ~controller_data4;
  
  // D4 pads
  pad04 = bitRead(controller_not_data4, 7);
  pad03 = bitRead(controller_not_data4, 6);
  pad12 = bitRead(controller_not_data4, 5);
  pad08 = bitRead(controller_not_data4, 4);

  
  // D3 pads
  pad02 = bitRead(controller_not_data3, 7);
  pad01 = bitRead(controller_not_data3, 6);
  pad05 = bitRead(controller_not_data3, 5);
  pad09 = bitRead(controller_not_data3, 4);
  pad06 = bitRead(controller_not_data3, 3);
  pad10 = bitRead(controller_not_data3, 2);
  pad11 = bitRead(controller_not_data3, 1);
  pad07 = bitRead(controller_not_data3, 0);
  
/*  
  Serial.print("Data 3: ");
  //Serial.println(controller_data3, BIN);
  printBinary(controller_not_data3, 8);
  Serial.println();
  
  Serial.print("Data 4: ");
  //Serial.println(controller_data4, BIN);
  printBinary(controller_not_data4, 8);
*/
 
}

dataForController_t getControllerData(void) {

  // Set up a place for our controller data
  //  Use the getBlankDataForController() function, since
  //  just declaring a fresh dataForController_t tends
  //  to get you one filled with junk from other, random
  //  values that were in those memory locations before
  dataForController_t controllerData = getBlankDataForController();
  // Since our buttons are all held high and
  //  pulled low when pressed, we use the "!"
  //  operator to invert the readings from the pins
  controllerData.triangleOn = pad03; 
  controllerData.circleOn = pad04;
  controllerData.squareOn = pad07;
  controllerData.crossOn = pad08;
  
  controllerData.dpadUpOn = pad01;
  controllerData.dpadDownOn = pad06;
  controllerData.dpadLeftOn = pad05;
  controllerData.dpadRightOn = pad02;
  
  controllerData.l1On = pad11;
  controllerData.r1On = pad12;
  
  controllerData.l2On = pad09;
  controllerData.r2On = pad10;
  
  //controllerData.l3On = 0;
  //controllerData.r3On = 0;
  
  //controllerData.selectOn = 0;
  //controllerData.startOn = 0;
  
  //controllerData.homeOn = 0;
  
  // Set the analog sticks
  //  Since analogRead(pin) returns a 10 bit value,
  //  we need to perform a bit shift operation to
  //  lose the 2 least significant bits and get an
  //  8 bit number that we can use  
  controllerData.leftStickX = 128;
  controllerData.leftStickY = 128;
  controllerData.rightStickX = 128;
  controllerData.rightStickY = 128;
  // And return the data!
  return controllerData;
}


void printBinary(int v, int num_places) {
    int mask=0, n;

    for (n=1; n<=num_places; n++) {
        mask = (mask << 1) | 0x0001;
    }
    v = v & mask;  // truncate v to specified number of places

    while(num_places) {

        if (v & (0x0001 << num_places-1)) {
             Serial.print("1");
        } else {
             Serial.print("0");
        }

        --num_places;
        if(((num_places%4) == 0) && (num_places != 0)) {
            Serial.print("_");
        }
    }
}
