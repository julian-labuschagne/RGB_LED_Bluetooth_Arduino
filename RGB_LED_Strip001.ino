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

    redColorValue = Serial.parseInt();
    EEPROM.write(0, redColorValue);
    
    greenColorValue = Serial.parseInt();
    EEPROM.write(1, greenColorValue);
    
    blueColorValue = Serial.parseInt();
    EEPROM.write(2, blueColorValue);
    
    if(Serial.read() == '#') {
      displayColor(redColorValue, greenColorValue, blueColorValue);
    }
    
    Serial.print("Red: ");
    Serial.println(redColorValue);
    
    Serial.print("Green: ");
    Serial.println(greenColorValue);
    
    Serial.print("Blue: ");
    Serial.println(blueColorValue);
    
  }
  
  //Serial.print("Color value: ");
  //Serial.println(colorValue);
  
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
    delay(30);  
  }
  
  for (int i = 0; i < 256; i++) {
    red_value = 0;
    green_value--;
    blue_value = i;
    
    displayColor(red_value, green_value, blue_value);
    delay(30);  
  }
  
  for (int i = 0; i < 256; i++) {
    red_value = i;
    green_value = 0;
    blue_value--;
    
    displayColor(red_value, green_value, blue_value);
    delay(30);  
  }
}
