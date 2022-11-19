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
//  Serial.begin(9600);

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
  Consumer.begin();
}

void loop() {
  char customKey = customKeypad.getKey();
  int pot = analogRead(potentiometerPIN);

  if (customKey){
    switch (customKey) {
      // == L1 ======================================
      case 'P':
        Consumer.write(0x192);
        break;
      case 'Q':
        Consumer.write(0x193);
        break;
      case 'R':
        Consumer.write(0x194);
        break;

      // == L2 ======================================
      case 'M':
        Consumer.write(0x195);
        break;
      case 'N':
        Consumer.write(0x196);
        break;
      case 'O':
        Consumer.write(0x197);
        break;

      // == L3 ======================================
      case 'I':
        Consumer.write(0x198);
        break;
      case 'J':
        Consumer.write(0x199);
        break;
      case 'K':
        Consumer.write(0x19A);
        break;
      case 'L':
        Consumer.write(0x19B);
        break;

      // == L4 ======================================
      case 'E':
        Consumer.write(0x19C);
        break;
      case 'F':
        Consumer.write(0x19D);
        break;
      case 'G':
        Consumer.write(0x19E);
        break;
      case 'H':
        Consumer.write(0x19F);
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
