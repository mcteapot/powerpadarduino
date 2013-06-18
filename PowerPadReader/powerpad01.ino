/* 
Reading a NES Controller
By Sebastian Tomczak
21 July 2007
Adelaide, Australia
*/

/* INITIALISATION */

int latch = 2; // set the latch pin
int clock = 3; // set the clock pin
int data1 = 4; // set the data in pin
int data3 = 5;
int data4 = 6;

byte controller_data1 = 0;
byte controller_data3 = 0;
byte controller_data4 = 0;

/* SETUP */
void setup() {
  //Serial.begin(57600);
  Serial.begin(9600);
  pinMode(latch,OUTPUT);
  pinMode(clock,OUTPUT);
  
  pinMode(data1,INPUT);
  pinMode(data3,INPUT);
  pinMode(data4,INPUT);
  
  digitalWrite(latch,HIGH);
  digitalWrite(clock,HIGH);
}

/* CONTROLLER READ */
void controllerRead() {
  controller_data1 = 0;
  controller_data3 = 0;
  controller_data4 = 0;
  digitalWrite(latch,LOW);
  digitalWrite(clock,LOW);
  
  digitalWrite(latch,HIGH);
  delayMicroseconds(2);
  digitalWrite(latch,LOW);
  
  controller_data1 = digitalRead(data1);
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

/* PROGRAM */
void loop() {
  controllerRead();

  //Serial.print("Data 1:");,.
  //Serial.println(controller_data1, BIN);
  
  Serial.print("Data 3: ");
  //Serial.println(controller_data3, BIN);
  printBinary(controller_data3, 8);
  Serial.println();
  
  Serial.print("Data 4: ");
  //Serial.println(controller_data4, BIN);
  printBinary(controller_data4, 8);
  Serial.println();

  delay(100);
}


void printBinary(int v, int num_places)
{
    int mask=0, n;

    for (n=1; n<=num_places; n++)
    {
        mask = (mask << 1) | 0x0001;
    }
    v = v & mask;  // truncate v to specified number of places

    while(num_places)
    {

        if (v & (0x0001 << num_places-1))
        {
             Serial.print("1");
        }
        else
        {
             Serial.print("0");
        }

        --num_places;
        if(((num_places%4) == 0) && (num_places != 0))
        {
            Serial.print("_");
        }
    }
}
