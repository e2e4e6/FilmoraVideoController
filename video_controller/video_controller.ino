#include <Keyboard.h>
#include <Encoder.h>
// NOTE: Tools -> Board -> Arduino Leonardo
// NOTE: Tools -> Programmator -> Arduino as ISP (ATmega32U4)

/*
Uses two controllers:
     
*/ 

enum {
  CR1_MOVE_LEFT,
  CR1_MOVE_RIGHT,
  CR1_PRESS,

  CR2_ROTATE_LEFT,
  CR2_ROTATE_RIGHT
};

const int CR1_OX_PIN = 0;
const int CR1_OY_PIN = 1;
const int CR1_SW_PIN = 4;

const int CR2_SW_PIN = 6;
const int CR2_DT_PIN = 7;
const int CR2_CLK_PIN = 8;

Encoder yellowKnob(7, 8);
int yellowPos = -999;

void setup() {
  Serial.begin(9600);
  pinMode(CR1_OX_PIN, INPUT);
  pinMode(CR1_OY_PIN, INPUT);         
  pinMode(CR1_SW_PIN, INPUT_PULLUP);

  pinMode(CR2_SW_PIN, INPUT);
  pinMode(CR2_DT_PIN, INPUT);
  pinMode(CR2_CLK_PIN, INPUT_PULLUP);
  Keyboard.begin();
}

bool blackReset = true;
long playTime = ~0;

void loop() {

  int sw1 = digitalRead(CR1_SW_PIN);
  int ox = analogRead(CR1_OX_PIN);
  int oy = analogRead(CR1_OY_PIN);

  if (ox == 0) {
    //Serial.println("Black down.");
    delay(100);
  }
  if (ox > 1000) {
    //Serial.println("Black up.");
    delay(100);
  }
  if (oy == 0 && blackReset) {
    //Serial.println("Black left.");
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_ARROW);
    Keyboard.releaseAll();
    blackReset = false;
  }
  if (oy > 1000 && blackReset) {
    //Serial.println("Black right.");
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_RIGHT_ARROW);
    Keyboard.releaseAll();
    blackReset = false;
  }
  
  if (sw1 == 0 && blackReset) {
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_ARROW);
    Keyboard.releaseAll();
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_ARROW);
    Keyboard.releaseAll();
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_ARROW);
    Keyboard.releaseAll();
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_ARROW);
    Keyboard.releaseAll();
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_ARROW);
    Keyboard.releaseAll();
    Keyboard.write(' ');
    Keyboard.releaseAll();
    blackReset = false;
    playTime = millis();
  }

  if (playTime != ~0 && (millis() - playTime) / 1000 > 5) {
    Keyboard.write(' ');
    Keyboard.releaseAll();
    playTime = ~0;
  }

  if (oy > 100 && oy < 1000 && sw1  != 0) {
    blackReset = true;
  }

  long newYellow;
  newYellow = yellowKnob.read();
  if (newYellow != yellowPos) {
    if (newYellow < yellowPos) {
      Keyboard.press(KEY_LEFT_ARROW);
      //delay(100);
      Keyboard.releaseAll();
    } else if (newYellow > yellowPos) {
      Keyboard.press(KEY_RIGHT_ARROW);
      //delay(100);
      Keyboard.releaseAll();
    }
    //Serial.print(newYellow);
    yellowPos = newYellow;
  }
  
  

  
}
