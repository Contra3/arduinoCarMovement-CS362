/*  Team Number: 28
 *   
 *  Project Name: Gas Gas Gas
 *  
 *  Abstract: 
 *  
 *  The need to step on the gas and go faster is one of the many necessities for a car. The project will accomplish that by constructing a remote control car that will 
 *  also incorporate a safety feature that is necessary for many cars and is incorporated into many in real life, modern cars - an anti-collision system. This car, not 
 *  only will it gas to fast and incorporate safety features to mitigate, if not prevent, collisions, it will owe tribute to Initial D an anime about street racing.
 *  
 *  
 *  Authors: Jon-Michael Hoang | jhoang6 | 657540122
 *           Ronny Recinos     | rrecin2 | 678597858
 *  
 *  Desc: This program will pretty much control the PS4, USB Shield, Bluetooth Module and the car motors
 *        There are quite a few libraries used to make everything work together. Using the PS4 controller
 *        we can map the buttons of the controllers to send signals to the Arduino to activate specific
 *        statements that will drive the car either forward or backwards, turn left or right, and also
 *        turn the speakers that are connected to the sensor Arduino ON or OFF
 *              
 *        
 *  References: 
 *              https://www.youtube.com/watch?v=dyjo_ggEtVU "Controlling DC Motors with the L298N H Bridge and Arduino"
 *              https://www.youtube.com/watch?v=cucp1-EmVRU "L298N H-Bridge Arduino 4WD" 
 *              https://github.com/felis/USB_Host_Shield_2.0
 *              https://www.arduino.cc/reference/en/language/functions/communication/serial/
 * 
 */


// Bluetooth Settings
#include <PS4BT.h>
#include <usbhub.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
#include <L298N.h>

/*
 * IN1 = WHITE WIRE
 * IN2 = YELLOW WIRE
 * 
 * IN3 = BLUE WIRE
 * IN4 = PURPLE WIRE
 * 
 * ENA = GRAY WIRE
 * ENB = GREEN WIRE
 */

// Handles the Left Side Motors
#define ENA 9
#define IN1 2
#define IN2 8

// Handles the Right Side Motors
#define IN3 4
#define IN4 7
#define ENB 3

char speakerOn[] = "option01";
char speakerOff[] = "option02";

USB Usb;
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
PS4BT PS4(&Btd, PAIR);

L298N motorR(ENA, IN1, IN2);
L298N motorL(ENB, IN3, IN4);


uint8_t carTrigger = 99;

int setSpeed = 255;
  
void setup() { 
  Serial.begin(9600);
  #if !defined(__MIPSEL__)
  while (!Serial); 
  #endif
  if (Usb.Init() == -1) {
    while (1); 
    }
    
  motorR.setSpeed(setSpeed * .9); // an integer between 0 and 255
  motorL.setSpeed(setSpeed * .9); // an integer between 0 and 255
}

void loop() {
  
  if (Serial.available())
  {
    int tofMeasure =  Serial.parseInt();
    //Serial.println(tofMeasure);
     
    // too close
    if (tofMeasure > 0 && tofMeasure <= 100)
    {
      //Serial.println("Speed is 75");
      setSpeed = 75;
    }
    // close
    else if (tofMeasure > 100 && tofMeasure <= 250)
    {
      //Serial.println("Speed is 100");
      setSpeed = 100;
    }
    // not close
    else
    {
      //Serial.println("Speed is 255");
      setSpeed = 255;
    }      
    
  }
  
  Usb.Task();
  if (PS4.connected()) {
    if (PS4.getButtonClick(PS)) { 
         PS4.disconnect(); 
    }
    else {
       // Move Car Backwards - *Note: Due to the location of the ToF sensor, we use the function forward() to go at a backward direction
       if(carTrigger == 0 ){
           motorR.setSpeed(setSpeed * .9); // an integer between 0 and 255
           motorL.setSpeed(setSpeed * .9); // an integer between 0 and 255
           motorR.forward();
           motorL.forward();
       }  
       // Move Car Forwards - *Note: Due to the location of the ToF sensor, we use the function backward() to go at a forward direction
       else if(carTrigger == 1){
           motorR.setSpeed(setSpeed * .9); // an integer between 0 and 255
           motorL.setSpeed(setSpeed * .9); // an integer between 0 and 255
           motorR.backward();
           motorL.backward();

       }
       // Stop Car
       else if(carTrigger == 2){
        
           motorR.stop();
           motorL.stop();
       }
       // Move Car Forward Left
       else if(carTrigger == 3){
          motorL.setSpeed(setSpeed);
          motorL.backward();

          motorR.setSpeed(setSpeed * .5);
          motorR.backward();
       }
       //Move Car Forward Right
       else if(carTrigger == 4){
          motorL.setSpeed(setSpeed * .5);
          motorL.backward();

          motorR.setSpeed(setSpeed);
          motorR.backward();
       }

      /*
       * CAR MOVEMENT BUTTONS
       */
       
      // Stops Car
      if (PS4.getButtonPress(L2)) {     
          carTrigger = 2;
      }

      // Moves the car forward
      if (PS4.getButtonPress(R2)) {
          carTrigger = 1;
      }

      // Moves the car backwards
      if (PS4.getButtonPress(R1)) {
         carTrigger = 0;
      }

      // Turns the car Forward Left
      if (PS4.getButtonPress(LEFT)){
         carTrigger = 3;
      }

      // Turns the car Forward Right
      if (PS4.getButtonPress(RIGHT)){
         carTrigger = 4;
      }

      /*
       * END OF CAR MOVEMENT BUTTONS
       */
      
      
      /*
       * SIGNALS TO OTHER ARDUINO BUTTONS
       */


      // Send Signal to turn ON the Speakers
      if (PS4.getButtonClick(SQUARE)){
          Serial.write(speakerOn, 8);
      }
    
    
      // Send Signal to turn OFF the Speakers
      if (PS4.getButtonClick(CIRCLE)){
          Serial.write(speakerOff, 8);
      }

      /*
       * END OF SIGNALS TO OTHER ARDUINO BUTTONS
       */

    }
 }


}
