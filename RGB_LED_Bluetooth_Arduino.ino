#include <EEPROM.h>

#define RED_LED     9
#define GREEN_LED   10
#define BLUE_LED    11

int colorValue = 0;

int red_value = 255;
int green_value = 0;
int blue_value = 0;

int redColorValue = 0;
int greenColorValue = 0;
int blueColorValue = 0;

int cycleDelay = 30;

int displayState = 0;

void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  
  redColorValue = EEPROM.read(0);
  greenColorValue = EEPROM.read(1);
  blueColorValue = EEPROM.read(2);
  
  displayColor(redColorValue, greenColorValue, blueColorValue);
}

void loop() {
  
  while(Serial.available() > 0) {
    
    char com = Serial.read();
    
    if(com == 's') {
      
      displayState = 0;
      
      redColorValue = Serial.parseInt();
      greenColorValue = Serial.parseInt();
      blueColorValue = Serial.parseInt();
      
      EEPROM.write(0, redColorValue);
      EEPROM.write(1, greenColorValue);
      EEPROM.write(2, blueColorValue);
      
      Serial.print("saved:");
      Serial.print(redColorValue);
      Serial.print(",");
      Serial.print(greenColorValue);
      Serial.print(",");
      Serial.println(blueColorValue);
    
    } else if (com == 'c') {
      displayState = 1;
      cycleDelay = Serial.parseInt();
    }
    
  }
  
  // Display a set color or cycle colors
  if (displayState == 0) {
    displayColor(redColorValue, greenColorValue, blueColorValue);
  } else if (displayState == 1) {
    cycleColor();
  }
  
}

void displayColor(int red, int green, int blue) {
  analogWrite(RED_LED, red);
  analogWrite(GREEN_LED, green);
  analogWrite(BLUE_LED, blue);
}

void cycleColor() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 256; i++) {
    red_value--;
    green_value = i;
    blue_value = 0;
    
    displayColor(red_value, green_value, blue_value);
    delay(cycleDelay);  
  }
  
  for (int i = 0; i < 256; i++) {
    red_value = 0;
    green_value--;
    blue_value = i;
    
    displayColor(red_value, green_value, blue_value);
    delay(cycleDelay);  
  }
  
  for (int i = 0; i < 256; i++) {
    red_value = i;
    green_value = 0;
    blue_value--;
    
    displayColor(red_value, green_value, blue_value);
    delay(cycleDelay);  
  }
}
