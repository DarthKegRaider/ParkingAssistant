#include <Adafruit_NeoPixel.h>
#include <NewPing.h> //include the library for the SR04 sonar distance sensor
#include <EEPROM.h> //this lets us access the EEPROM memory
#define PIN 3

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

const int trigPin = 11; //set the distance sensor trigger pin to A0
const int echoPin = 10; //the sonar echo pin
const int buttonPin = 2; //the button

NewPing sonar(trigPin, echoPin, 240); //start the distance sensor (Receive Pin, SendPin, Max Distance INCHES)

const int minDeviation = 5; //the number of inches of movement required to count as moving
const int timeout = 10; //the number of seconds to keep the leds on after movement stops
const int ledDistance = 6; //the distance in inches each led covers

int idealDistance = 2; //this is the perfect distance to the car read from the memory
int rawSonar; //this is the raw data from the distance sensor
int distance; //the distance to the vehicle
int prevDistance = 0; //the previous distance to the vehicle
unsigned long lastMoved = 0; //the millis reading of the last movement


void setup() { 
  pinMode(buttonPin, INPUT_PULLUP); //set button as input with internal pull-up resitors

  if (EEPROM.read(0) != 255) { //read the memory, it will read 255 if it's never been written to
    idealDistance = EEPROM.read(0); //set the idealDistance from the memory
  }
  strip.begin();
  allOff(); // turn all pixels off
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  delay(100);

  rawSonar = sonar.ping_median(5); //get 5 readings and average them

  if (rawSonar != 0) { //the distance sensor sends a 0 when nothing is in range
    distance = rawSonar / US_ROUNDTRIP_IN; //convert the raw data to inches
    distance -= idealDistance; //subtract the ideal distance from the reading, giving us the distance to go
  }
  else {
  strip.show(); // Display Pixel
  }

  if (abs(distance - prevDistance) >= minDeviation) { //if the car has moved since last read
    lastMoved = 0; //reset the sleep timer

    prevDistance = distance; //reset the distance last read

    if (distance < ledDistance * 9 && distance >= ledDistance * 8) { //if it's in the 1st led's range
allOff(); //turn the LEDs off
for (int i = 0; i < 1; i++) {
        strip.setPixelColor(i, 0, 255, 0); // Sets pixel #0 and #1 Green
        }
      strip.show();
    
    }
    else if (distance < ledDistance * 8 && distance >= ledDistance * 7) { //if in range of the 2nd led
allOff(); //turn the LEDs off
for (int i = 0; i < 3; i++) {
        strip.setPixelColor(i, 0, 255, 0); // Sets pixel #0 through #3 Green
        }
      strip.show();
    }
    else if (distance < ledDistance * 7 && distance >= ledDistance * 6) { //if in range of the 3rd led
      allOff(); //turn the LEDs off
for (int i = 0; i < 5; i++) {
        strip.setPixelColor(i, 0, 255, 0); // Sets pixel #0 through #5 Green
        }
      strip.show();
    }
    else if (distance < ledDistance * 6 && distance >= ledDistance * 5) { //if in range of the 4th led
allOff(); //turn the LEDs off
for (int i = 0; i < 7; i++) {
        strip.setPixelColor(i, 0, 255, 0); // Sets pixel #0 through #7 Green
        }
      strip.show();
    }
    else if (distance < ledDistance * 5 && distance >= ledDistance * 4) { //if in the 5th led
allOff(); //turn the LEDs off
for (int i = 0; i < 9; i++) {
        strip.setPixelColor(i, 0, 255, 0); // Sets pixel #0 through #9 Green
        }
      strip.show();
    }
    else if (distance < ledDistance * 4 && distance >= ledDistance * 3) { //if in range of the 6th led
allOff(); //turn the LEDs off
 for (int i = 0; i < 11; i++) {
        strip.setPixelColor(i, 0, 255, 0); // Sets pixel #0 through #11 Green
        }
      strip.show();
    }
    else if (distance < ledDistance * 3 && distance >= ledDistance * 2) { //if in range of the 7th led
allOff(); //turn the LEDs off
for (int i = 0; i < 13; i++) {
        strip.setPixelColor(i, 0, 255, 0); // Sets pixel #0 through #13 Green
        }
      strip.show();
    }
    else if (distance < ledDistance * 2 && distance >= ledDistance) { //if in range of the 8th led
allOff(); //turn the LEDs off
for (int i = 0; i < 15; i++) {
        strip.setPixelColor(i, 0, 255, 0); // Sets all pixels Green
        }
      strip.show();
    }
    else if (distance <= idealDistance) { //if in the stop position

      allOnRed();  //Sets all pixels to red
      strip.show();
    }
  }
  else { //if the car isn't moving
    if (lastMoved == 0) { //if the timer hasn't been started
      lastMoved = millis(); //set the timer
    }

    if (lastMoved != 0 && millis() - lastMoved >= timeout * 1000) { //if the timer is set and past the timeout
      allOff(); //turn off the leds
      lastMoved = 0; //turn off the timer
    }
  }

  //this checks the button
  if (digitalRead(buttonPin) == LOW) { //if the button is being pressed
    rawSonar = sonar.ping_median(30); //get 30 readings and average them

    if (rawSonar != 0) { //the distance sensor sends a 0 when nothing is in range
      distance = rawSonar / US_ROUNDTRIP_IN; //convert the raw data the inches

      EEPROM.write(0, distance); //write the distance to the memory
      idealDistance = distance; //set the idealDistance

      flashGreen(); //show success
    }
    else { //if out of range
      flashRed(); //show error
    }
  }
}


void flashGreen() { //this flashes the green LEDs to show success
  allOff();//clear the leds
  allOnGreen(); //turn the green leds on
  delay(500);
  allOff(); //turn all the leds off
  delay(500);
  allOnGreen(); //turn the green leds on
  delay(500);
  allOff(); //turn the green leds off
}

void flashRed() { //this flashes the red LEDs to show success
  allOff(); //clear the leds
  allOnRed(); //turn the red leds on
  delay(500);
  allOff(); //turn all the leds off
  delay(500);
  allOnRed(); //turn the red leds on
  delay(500);
  allOff(); //turn all the leds off
}

// All Pixels Off
void allOff() {
for (int i = 16; i != -1; i--) {
        strip.setPixelColor(i, 0, 0, 0); // Pixel #0
        }
      strip.show();
}

//All Pixels on RED
void allOnRed() {
  
for (int i = 15; i != -1; i--) {
        strip.setPixelColor(i, 255, 0, 0); // Pixel #0 green
        }        
      strip.show();
}


//All Pixels on Green
void allOnGreen() {

for (int i = 15; i != -1; i--) {
        strip.setPixelColor(i, 0, 255, 0); // Pixel #0 green
        }      
      strip.show();
}
