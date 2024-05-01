#include <Keypad.h>
#include <HID-Project.h>
#define LED_GREEN_1 18
#define LED_GREEN_2 15
#define LED_RED 14
#define LED_YELLOW 16
#define potentiometerPIN 2

int LED_GREEN_1_STATE = LOW;
int TIMER = 0;
int LED_GREEN_2_STATE = LOW;
int LED_RED_STATE = LOW;
int LED_YELLOW_STATE = LOW;

const byte COLS = 4;
const byte ROWS = 5;

byte colPins[COLS] = { 5, 4, 3, 2 };
byte rowPins[ROWS] = { 6, 7, 8, 9, 10 };

char hexaKeys[COLS][ROWS] = {
  { 'X', 'X', 'J', 'N', 'R' },
  { 'C', 'F', 'I', 'M', 'Q' },
  { 'B', 'E', 'H', 'L', 'P' },
  { 'A', 'D', 'G', 'K', 'O' }
};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), colPins, rowPins, COLS, ROWS);

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
  Keyboard.begin();
}

void loop() {
  char customKey = customKeypad.getKey();
  int pot = analogRead(potentiometerPIN);

  if (customKey) {
    switch (customKey) {
      // == L1 ======================================
      case 'A':
        // Keyboard.write('A');
        Keyboard.write(KEY_F13);
        break;
      case 'B':
        // Keyboard.write('B');
        Keyboard.write(KEY_F14);
        break;
      case 'C':
        // Keyboard.write('C');
        Keyboard.write(KEY_F15);
        break;

      // == L2 ======================================
      case 'D':
        // Keyboard.write('D');
        Keyboard.write(KEY_F16);
        break;
      case 'E':
        // Keyboard.write('E');
        Keyboard.write(KEY_F17);
        break;
      case 'F':
        // Keyboard.write('F');
        Keyboard.write(KEY_F18);
        break;

      // == L3 ======================================
      case 'G':
        // Keyboard.write('G');
        Keyboard.write(KEY_INTERNATIONAL2);
        break;
      case 'H':
        // Keyboard.write('H');
        Keyboard.write(KEY_MENU2);
        break;
      case 'I':
        // Keyboard.write('I');
        Keyboard.write(KEY_EXECUTE);
        break;
      case 'J':
        // Keyboard.write('J');
        Keyboard.write(KEY_HELP);
        break;

      // == L4 ======================================
      case 'K':
        // Keyboard.write('K');
        Keyboard.write(KEY_INTERNATIONAL4);
        break;
      case 'L':
        // Keyboard.write('L');
        Keyboard.write(KEY_INTERNATIONAL5);
        break;
      case 'M':
        // Keyboard.write('M');
        Keyboard.write(KEY_LANG3);
        break;
      case 'N':
        // Keyboard.write('N');
        Keyboard.write(KEY_LANG4);
        break;

      // == L5 ======================================
      case 'O':
        // Keyboard.write('O');
        LED_GREEN_1_STATE = !LED_GREEN_1_STATE;
        digitalWrite(LED_GREEN_1, LED_GREEN_1_STATE);
        break;
      case 'P':
        // Keyboard.write('P');
        LED_GREEN_2_STATE = !LED_GREEN_2_STATE;
        digitalWrite(LED_GREEN_2, LED_GREEN_2_STATE);
        break;
      case 'Q':
        // Keyboard.write('Q');
        LED_YELLOW_STATE = !LED_YELLOW_STATE;
        digitalWrite(LED_YELLOW, LED_YELLOW_STATE);
          if (LED_YELLOW_STATE == HIGH)
            Mouse.press(MOUSE_LEFT);
          else
            Mouse.release(MOUSE_LEFT);
        break;
      case 'R':
        // Keyboard.write('R');
        LED_RED_STATE = !LED_RED_STATE;
        digitalWrite(LED_RED, LED_RED_STATE);
        if (LED_RED_STATE == HIGH)
          Mouse.press(MOUSE_RIGHT);
        else
          Mouse.release(MOUSE_RIGHT);
        break;
    }
  }

  if (LED_GREEN_1_STATE == HIGH || LED_GREEN_2_STATE == HIGH) {
    TIMER += 1;
    if (TIMER >= pot) {
      if (LED_GREEN_1_STATE == HIGH) {15
        Mouse.click(MOUSE_LEFT);
      }
      if (LED_GREEN_2_STATE == HIGH) {
        Mouse.click(MOUSE_RIGHT);
      }
      TIMER = 0;
    }
  }

  delay(1);
}
