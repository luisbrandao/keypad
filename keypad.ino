#include <Keypad.h>
#include <Mouse.h>
#define LED_GREEN_1 15
#define LED_GREEN_2 14
#define LED_RED 16
#define LED_YELLOW 18
#define potentiometerPIN 2

int LED_GREEN_1_STATE = LOW;
int LED_GREEN_1_COUNT = 0;
int LED_GREEN_2_STATE = LOW;
int LED_RED_STATE = LOW;
int LED_YELLOW_STATE = LOW;


const byte ROWS = 4; 
const byte COLS = 5; 

char hexaKeys[ROWS][COLS] = {
  {'A', 'E', 'I', 'M','P'},
  {'B', 'F', 'J', 'N','Q'},
  {'C', 'G', 'K', 'O','R'},
  {'D', 'H', 'L', 'XX','XX'}
};

byte rowPins[ROWS] = {5, 4, 3, 2}; 
byte colPins[COLS] = {6, 7, 8, 9, 10}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup() {
  Serial.begin(9600);

  // Seta os leds
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN_1, OUTPUT);
  pinMode(LED_GREEN_2, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  
  // Leds Desligados
  digitalWrite(LED_RED, LED_RED_STATE);
  digitalWrite(LED_GREEN_1, LED_GREEN_1_STATE);
  digitalWrite(LED_GREEN_2, LED_GREEN_2_STATE);
  digitalWrite(LED_YELLOW, LED_YELLOW_STATE);
  
  // Incia as libs de IO com o PC
  Mouse.begin();
}

void loop() {
  //Acende o led
  char customKey = customKeypad.getKey();
  int pot = analogRead(potentiometerPIN);
  
  if (customKey){
    switch (customKey) {
      case 'A':
        LED_GREEN_1_STATE = !LED_GREEN_1_STATE;
        digitalWrite(LED_GREEN_1, LED_GREEN_1_STATE);
      break;
      case 'B':
        LED_GREEN_2_STATE = !LED_GREEN_2_STATE;
        digitalWrite(LED_GREEN_2, LED_GREEN_2_STATE);
      break;
      case 'C':
        LED_YELLOW_STATE = !LED_YELLOW_STATE;
        digitalWrite(LED_YELLOW, LED_YELLOW_STATE);
      break;
      case 'D':
        LED_RED_STATE = !LED_RED_STATE;
        digitalWrite(LED_RED, LED_RED_STATE);
      break;
    }
  }

  if (LED_GREEN_1_STATE == HIGH) {
	  LED_GREEN_1_COUNT += 1;
      if (LED_GREEN_1_COUNT >= pot) {
        Mouse.click();
        LED_GREEN_1_COUNT = 0;
      }
  }
  
  delay(1);
}