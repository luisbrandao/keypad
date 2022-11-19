#include <Keypad.h>
#include <HID-Project.h>
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
  {'D', 'H', 'L', 'X','X'}
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
  AbsoluteMouse.begin();
}

void loop() {
  char customKey = customKeypad.getKey();
  int pot = analogRead(potentiometerPIN);

  if (customKey){
    switch (customKey) {
      // == L1 ======================================
      case 'P':
        break;
      case 'Q':
        break;
      case 'R':
        break;

      // == L2 ======================================
      case 'M':
        break;
      case 'N':
        break;
      case 'O':
        break;

      // == L3 ======================================
      case 'I':
        break;
      case 'J':
        break;
      case 'K':
        break;
      case 'L':
        break;

      // == L4 ======================================
      case 'E':
        break;
      case 'F':
        break;
      case 'G':
        break;
      case 'H':
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
        AbsoluteMouse.click(MOUSE_LEFT);
      }
      if (LED_GREEN_2_STATE == HIGH){
        AbsoluteMouse.click(MOUSE_RIGHT);
      }
      TIMER = 0;
    }
  }

  delay(1);
}
