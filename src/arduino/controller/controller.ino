/******************************************************************************
 * ART 150 - Project 5 - Final Project
 * Videogame System | By: Kevin Kowalaski
 ******************************************************************************
 * Arduino code handling inputs to and from
 * the Processing software according to 
 * states of installed hardware
 ******************************************************************************
 * Arduino Uno R3
 * 2-axis Joystick
 * Momentary Push Buttons [x2]
 * Character Display [with adapter board]
 * Processing Sofware Interaction
 ******************************************************************************
 * Helpful link used for Arduino/Processing communication:
 * https://learn.sparkfun.com/tutorials/connecting-arduino-to-processing/all
 ******************************************************************************/

//#include <LiquidCrystal.h>
#include "Wire.h" // For I2C
#include "LCD.h" // For LCD
#include "LiquidCrystal_I2C.h" // Added library*

/// when using the LCD adapter board, SDA -> A4 and SCL -> A5
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7); // 0x27 is the default I2C bus address of the backpack-see article

#define Vx A0 // Define / Equate “Vx” with A0, the pin where Vx is connected
#define Vy A1 // Define / Equate “Vy” with A1, the pin where Vy is connected
#define Button A2 // Define / Equate Button with A2, the pin where the button is connected

int blue_btn_state = 0;
int pin_blue_btn = 2;
int blck_btn_state = 0;
int pin_blck_btn = 4;

// initial setup
void setup() {
  
  // initalize hardware inputs
  pinMode(pin_blue_btn, INPUT_PULLUP);
  pinMode(pin_blck_btn, INPUT_PULLUP);

  pinMode(Vx, INPUT); // Configure Vx (A0) as an Input
  pinMode(Vy, INPUT); // Configure Vy (A1) as an Input
  pinMode(Button, INPUT_PULLUP); // Configure Button (A2) as an Input, internally “pulled-up” to 5V
  
  // initialize hardware outputs
  lcd.begin(16, 2);
  lcd.setBacklightPin(3,POSITIVE); // BL, BL_POL
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0); //lcd.home();
  lcd.print("Welcome, player!");
  lcd.setCursor(0, 1);
  lcd.print("Choose a game...");
  
  // initialize console output
  Serial.begin(9600);
  Serial.println("ART 150 - Project 5 - Final Project");
  Serial.println("Videogame System | By: Kevin Kowalski");
  Serial.println("=====================================");
  establishContact();
}

// main program loop
void loop() {

  int x_dir, y_dir, btn;

  x_dir = analogRead(Vx); // Read the analog value of Vx (Analog Values are from 0-1023 which equate to 0V to 5V)
  y_dir = analogRead(Vy); // Read the analog value of Vy
  btn = digitalRead(Button); // Read the button. When the button is open (unpushed),
  // the input will read High (+5V)
  // When the button is closed (pressed), the input pin
  // is connected to ground and will read Low (0V)
  
  // read direction of joystick as character
  char dir = getJoyStickDirection(x_dir, y_dir);
  
  // read high or low state of buttons
  blue_btn_state = digitalRead(pin_blue_btn);
  blck_btn_state = digitalRead(pin_blck_btn);

  // build string with all current inputs encoded
  String inputs = build_input(dir, blue_btn_state, blck_btn_state);
  
  // read input from Processing to determine what LCD displays
  if (Serial.available() > 0) {
      // get input from Processing
      Serial.println(inputs);
      int val = Serial.read();

      // main menu
      if (val == 1) {
        lcd.setCursor(0, 0); //lcd.home();
        lcd.print("Welcome, player!");
        lcd.setCursor(0, 1);
        lcd.print("Choose a game...");
      }

      // calibration menu
      else if (val == 2) {
        lcd.home();
        lcd.clear();
        lcd.print(">> Test <<");
        //lcd.blink();
      }

      // blackjack game
      else if (val == 3) {
        lcd.home();
        lcd.clear();
        lcd.print("Blackjack!");
        lcd.setCursor(2, 1);
        lcd.print("Feeling lucky?");
      }

      // gravity platformer game
      else if (val == 4) {
        lcd.home();
        lcd.clear();
        lcd.print("Use gravity to");
        lcd.setCursor(0, 1);
        lcd.print("reach the goal!");
      }
  }
  
  delay(100);       // input delay
}

// confirm Processing is accepting inputs by checking for an 'A'
void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("A");   // send a capital A
    delay(300);
  }
}


// -----------------------------------------------------------------------
// CUSTOM FUNCTIONS BELOW
// -----------------------------------------------------------------------

// translates joy stick inputs as string directions
// note: prioritizes horizontal direction over vertical
char getJoyStickDirection(int x, int y){
  char result = 'C';  // at center position

  if (x < 256 /*&& y > 256 && y < 768*/) {
    result = 'R';
  }
  else if (x > 768 /*&& y > 256 && y < 768*/) {
    result = 'L';
  }
  else if (y < 256) {
    result = 'U';
  }
  else if (y > 768) {
    result = 'D';
  }
  
  return result;
}

// given hardware inputs, build readable input for Processing
// in form of "DIR-BLU-BLK" i.e. "C01" (where 0 is pushed down, 1 is not)
String build_input(char d, int blu, int blck) {
  String result = "";
  result += d;
  result += blu;
  result += blck;
  return result;
}
