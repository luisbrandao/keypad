#include <Keypad.h>
#include <Mouse.h>
#include <Keyboard.h>
#define LED_GREEN_1 15
#define LED_GREEN_2 14
#define LED_RED 16
#define LED_YELLOW 18
#define potentiometerPIN 2

int LED_GREEN_1_STATE = LOW;
int TIMER = 0;
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
  Keyboard.begin();
}

void loop() {
  char customKey = customKeypad.getKey();
  int pot = analogRead(potentiometerPIN);
  
  if (customKey){
    switch (customKey) {
      // == L1 ======================================
      case 'P':
        Keyboard.write(0xF0); // f13
        break;
      case 'Q':
        Keyboard.write(0xF1); // f14
        break;
      case 'R':
        Keyboard.write(0xF2); // f15
        break;

      // == L2 ======================================
      case 'M':
        Keyboard.write(0xF3); // f16
        break;
      case 'N':
        Keyboard.write(0xF4); // f17
        break;
      case 'O':
        Keyboard.write(0xF5); // f18
        break;

      // == L3 ======================================
      case 'I':
        Keyboard.write(0x1008FF1D); // f16
        break;
      case 'J':
        Keyboard.write(0x9E0);
        break;
      case 'K':
        Keyboard.write(0xEB);
        break;        
      case 'L':
        Keyboard.write(0xEC);
        break;

      // == L4 ======================================
      case 'E':
        Keyboard.write(0xED);
        break;
      case 'F':
        Keyboard.write(0xEF);
        break;
      case 'G':
        Keyboard.write(0xEF);  // =
        break;
      case 'H':
        Keyboard.write(0xD0);  //Pause
        break;



      // == L5 ======================================
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


  if (LED_GREEN_1_STATE == HIGH || LED_GREEN_2_STATE == HIGH) {
    TIMER += 1;
    if (TIMER >= pot) {
      if (LED_GREEN_1_STATE == HIGH){
        Mouse.click(MOUSE_LEFT);
      }
      if (LED_GREEN_2_STATE == HIGH){
        Mouse.click(MOUSE_RIGHT);
      }
      TIMER = 0;
    }
  }
 
  delay(1);
}