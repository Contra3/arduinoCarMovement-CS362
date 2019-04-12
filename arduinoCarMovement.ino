// Bluetooth Settings
#include <PS4BT.h>
#include <usbhub.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
PS4BT PS4(&Btd, PAIR);
//End Bluetooth Settings

  int ML1 = 5;
  int ML2 = 4;
  int MR1 = 13;
  int MR2 = 12;
  
  
  int EL = 3;   
  int ER = 11; 



void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));

    pinMode(ER, OUTPUT); 
    pinMode(EL, OUTPUT); 
    pinMode(ML1, OUTPUT); 
    pinMode(ML2, OUTPUT); 
    pinMode(MR1, OUTPUT); 
    pinMode(MR2, OUTPUT); 
}

//Functions that will move the robot

void goForward(){
     digitalWrite(ML1, HIGH);
     digitalWrite(ML2, LOW);
     analogWrite(EL, 200);


     digitalWrite(MR2, HIGH);
     digitalWrite(MR1, LOW); 
     analogWrite(ER, 200);
}

void goBackwards(){
    digitalWrite(ML1, LOW);
    digitalWrite(ML2, HIGH);
    analogWrite(EL, 200);


    digitalWrite(MR2, LOW);
    digitalWrite(MR1, HIGH); 
    analogWrite(ER, 200);
}

void moveLeft(){
  /*
   * TODO:
   */
}

void moveRight(){
  /*
   * TODO:
   */
}

void stopCar(){
     digitalWrite(ML1, LOW);
     digitalWrite(ML2, LOW);
     digitalWrite(MR1, LOW);
     digitalWrite(MR2, LOW);
}


void loop() {
  
  Usb.Task();

  if (PS4.connected()) {
    
    if (PS4.getButtonClick(PS)) {
      PS4.disconnect();
    }
    else {
      if (PS4.getButtonPress(TRIANGLE)) {
        /*
         * TODO:
         */
      }
      
      if (PS4.getButtonPress(CIRCLE)) {     
        /*
         * TODO:
         */  
      }
      if (PS4.getButtonPress(CROSS)) {
        goForward();
      }
      
      if (PS4.getButtonPress(SQUARE)) {
        goBackwards(); 
      }

      if (PS4.getButtonPress(LEFT)) { moveLeft(); } 
      if (PS4.getButtonPress(RIGHT)) { moveRight();}    
      
      if (PS4.getButtonPress(L1)){
        /*
         * TODO: Possible Feature
         */        
        }
      if (PS4.getButtonPress(L2)){
        /*
         * TODO: Possible Feature
         */       
        }
      if (PS4.getButtonPress(R1)){
        /*
         * TODO: Possible Feature
         */     
        }
      if (PS4.getButtonPress(R2)){
         /*
         * TODO: Possible Feature
         */     
        }
    }

    stopCar();
  }
}
