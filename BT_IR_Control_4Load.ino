#include <EEPROM.h>
#include <IRremote.h>
#include <SoftwareSerial.h>
SoftwareSerial BT_Serial(2, 3); // RX, TX

const int RECV_PIN=A5;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define Relay1 4 // Load1 Pin Out
#define Relay2 5 // Load2 Pin Out
#define Relay3 6 // Load3 Pin Out
#define Relay4 7 // Load4 Pin Out

char bt_data; // variable to receive data from the serial port
int load1, load2, load3, load4, power;

void setup(){
Serial.begin(9600);
BT_Serial.begin(9600); 

irrecv.enableIRIn(); // Start the receiver
irrecv.blink13(true);

pinMode(Relay1, OUTPUT); digitalWrite(Relay1, 1); 
pinMode(Relay2, OUTPUT); digitalWrite(Relay2, 1); 
pinMode(Relay3, OUTPUT); digitalWrite(Relay3, 1); 
pinMode(Relay4, OUTPUT); digitalWrite(Relay4, 1); 
  
load1 = EEPROM.read(1);
load2 = EEPROM.read(2);
load3 = EEPROM.read(3);
load4 = EEPROM.read(4);

power = EEPROM.read(5);
delay(500); 
}

void loop() {
if(irrecv.decode(&results)){
 Serial.println(results.value,HEX);
  
     if(results.value==0xFFB04F){ // For Load1 On  
load1 = 0; 
EEPROM.write(1, load1);  
}
else if(results.value==0xFF6897){ // For Load1 Off 
load1 = 1; 
EEPROM.write(1, load1);  
}

else if(results.value==0xFF7A85){ // For Load2 On 
load2 = 0; 
EEPROM.write(2, load2);  
}
else if(results.value==0xFF30CF){ // For Load2 Off 
load2 = 1; 
EEPROM.write(2, load2);  
}

else if(results.value==0xFF5AA5){ // For Load3 On 
load3 = 0; 
EEPROM.write(3, load3);  
}
else if(results.value==0xFF10EF){ // For Load3 Off 
load3 = 1; 
EEPROM.write(3, load3);  
}

else if(results.value==0xFF52AD){ // For Load4 On 
load4 = 0; 
EEPROM.write(4, load4);  
}
else if(results.value==0xFF42BD){ // For Load4 Off 
load4 = 1; 
EEPROM.write(4, load4);  
}

else if(results.value==0xFFE21D){ // For Power On 
power = 0; 
EEPROM.write(5, power);     
}    
else if(results.value==0xFFA25D){ // For Power Off
power = 1; 
EEPROM.write(5, power); 
}
    
 irrecv.resume(); // Receive the next value
 delay(100);
 }

if(BT_Serial.available()>0){bt_data = BT_Serial.read();}

if(bt_data == 'A'){load1=0;EEPROM.write(1, load1);}
if(bt_data == 'a'){load1=1;EEPROM.write(1, load1);}

if(bt_data == 'B'){load2=0;EEPROM.write(2, load2);}
if(bt_data == 'b'){load2=1;EEPROM.write(2, load2);}

if(bt_data == 'C'){load3=0;EEPROM.write(3, load3);}
if(bt_data == 'c'){load3=1;EEPROM.write(3, load3);}

if(bt_data == 'D'){load4=0;EEPROM.write(4, load4);}
if(bt_data == 'd'){load4=1;EEPROM.write(4, load4);}

if(bt_data == 'E'){power=0;EEPROM.write(5, power);}
if(bt_data == 'e'){power=1;EEPROM.write(5, power);}

bt_data = '0';
  
if(power==1){  
digitalWrite(Relay1, 1); 
digitalWrite(Relay2, 1); 
digitalWrite(Relay3, 1); 
digitalWrite(Relay4, 1); 
}else{
digitalWrite(Relay1, load1); 
digitalWrite(Relay2, load2); 
digitalWrite(Relay3, load3); 
digitalWrite(Relay4, load4);
}

BT_Serial.print(power); //send distance to MIT App
BT_Serial.print(";");
BT_Serial.print(load1); //send distance to MIT App 
BT_Serial.print(";");
BT_Serial.print(load2); //send distance to MIT App 
BT_Serial.print(";");
BT_Serial.print(load3); //send distance to MIT App 
BT_Serial.print(";");
BT_Serial.print(load4); //send distance to MIT App 
BT_Serial.println(";");
  
delay(500);  
}
