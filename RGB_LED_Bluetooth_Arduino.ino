#include <EEPROM.h>

#define RED_LED     9
#define GREEN_LED   10
#define BLUE_LED    11

#define CMD_LENGTH 64

int colorValue = 0;

int red_value = 255;
int green_value = 0;
int blue_value = 0;

int redColorValue = 0;
int greenColorValue = 0;
int blueColorValue = 0;

int cycleDelay = 30;

int displayState = 0;

String serial_command = "";

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
  
  if(Serial.available()) {
    
    char c = Serial.read();
    
    if (c == 'c') {
      int r = Serial.parseInt();
      int g = Serial.parseInt();
      int b = Serial.parseInt();

      displayColor(r, g, b);
    }
    
    
    
    //commandParse(serial_command);
  }
  
}

void commandParse(String cmd) {
  
  cmd.trim();
  //Serial.println(cmd);
  
  if (cmd.equals("AT")) {
    Serial.println("OK");
  } 
  else if (cmd.startsWith("SETCOLOR", 3)) {
    //Serial.println("Set the color");
    
    //------------------------------
    int redStart = cmd.indexOf('=');
    int redEnd = cmd.indexOf(',');
    
    int greenStart = cmd.indexOf(',');
    int greenEnd = cmd.indexOf(',', greenStart + 1);
    
    //int blueStart = cmd.indexOf(',', greenStart + 1);
    //int blueEnd = cmd.indexOf(',', greenStart + 1);
    int blueStart = greenEnd + 1;
    
    // ------------------------------------------
    String red = cmd.substring(redStart + 1, redEnd);
    int r = red.toInt();
    
    String green = cmd.substring(greenStart + 1, greenEnd);
    int g = green.toInt();
    
    String blue = cmd.substring(blueStart);
    int b = blue.toInt();
    
    //Serial.println(r);
    //Serial.println(g);
    //Serial.println(b);
    
    displayColor(r, g, b);
      
    //Serial.println("OK");
  
  } 
  else if (cmd.startsWith("SAVECOLOR", 3)) {
    Serial.println("Save the color");
    Serial.println("OK");
  }
  else {
    Serial.println("Unknown command");
    Serial.println("ERROR");
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
