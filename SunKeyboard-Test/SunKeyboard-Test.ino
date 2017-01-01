/*
 * Test Program for Sun Type 5 Keyboard
 * Ben Rockwood <benr@cuddletech.com> 1/1/17
 * 
 * Developed on Arduino Micro
 * MiniDIN 8a Adapter P/N: MD-80PL100 
 * Wiring:
 *    Keyboard Pin 2 (White): GND
 *    Keyboard Pin 8 (Red): +5V
 *    Keyboard Pin 6 (Yellow): Arduino Pin D10 (Serial RX)
 *    Keyboard Pin 5 (Green): Aruidno Pin D11 (Serial TX)
 */
#include <SoftwareSerial.h>

//Software serial for Sun KBD
SoftwareSerial sunSerial(10, 11, true);

void setup() {
  //Normal serial port init for monitoring
  Serial.begin(1200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  sunSerial.begin(1200);
}

void loop() {
  char c = sunSerial.read();
  //not sure why we're getting this spamming out so let's filter for now (inverse of 0 i guess)
  if (c != 0xFFFFFFFF) {
    Serial.print(c, DEC);
    Serial.print("\t0x");
    Serial.print(c, HEX);
    Serial.print(":\t");
    printKey(c);
    Serial.print("\n");
  }
}

void printKey(int key){
 if (key < 0) {
  key = 128 + key;
  Serial.print("Key Up: ");
 } else if (key == 127) {
  Serial.print("All Keys Released");
 } else {
  Serial.print("Key Down: ");
 }
  
 switch(key){
  case 29: // Esc
          Serial.print("Esc");
          break;

  case 30: // 1
          Serial.print("1");
          break;

  case 31: // 2
          Serial.print("2");
          break;

  case 32: // 3
          Serial.print("3");
          break;

  case 33: // 4
          Serial.print("4");
          break;

  case 34: // 5
          Serial.print("5");
          break;

  case 35: // 6
          Serial.print("6");
          break;

  case 36: // 7
          Serial.print("7");
          break;

  case 37: // 8
          Serial.print("8");
          break;

  case 38: // 9
          Serial.print("9");
          break;

  case 39: // 0
          Serial.print("0");
          break;

  case 40: // minus
          Serial.print("minus");
          break;

  case 41: // equal
          Serial.print("equal");
          break;

  case 43: // BackSpace
          Serial.print("BackSpace");
          break;

  case 53: // Tab
          Serial.print("Tab");
          break;

  case 54: // Q
          Serial.print("Q");
          break;

  case 55: // W
          Serial.print("W");
          break;

  case 56: // E
          Serial.print("E");
          break;

  case 57: // R
          Serial.print("R");
          break;

  case 58: // T
          Serial.print("T");
          break;

  case 59: // Y
          Serial.print("Y");
          break;

  case 60: // U
          Serial.print("U");
          break;

  case 61: // I
          Serial.print("I");
          break;

  case 62: // O
          Serial.print("O");
          break;

  case 63: // P
          Serial.print("P");
          break;

  case 64: // [
          Serial.print("[");
          break;

  case 65: // ]
          Serial.print("]");
          break;

  case 89: // Return
          Serial.print("Return");
          break;

  case 76: // Ctrl_L
          Serial.print("Ctrl_L");
          break;

  case 77: // A
          Serial.print("A");
          break;

  case 78: // S
          Serial.print("S");
          break;

  case 79: // D
          Serial.print("D");
          break;

  case 80: // F
          Serial.print("F");
          break;

  case 81: // G
          Serial.print("G");
          break;

  case 82: // H
          Serial.print("H");
          break;

  case 83: // J
          Serial.print("J");
          break;

  case 84: // K
          Serial.print("K");
          break;

  case 85: // L
          Serial.print("L");
          break;

  case 86: // ;
          Serial.print(";");
          break;

  case 87: // apostr.
          Serial.print("apostr.");
          break;

  case 42: // grave/tilde
          Serial.print("grave/tilde");
          break;

  case 99: // Shift_L
          Serial.print("Shift_L");
          break;

  case 88: // backslash
          Serial.print("backslash");
          break;

  case 100: // Z
          Serial.print("Z");
          break;

  case 101: // X
          Serial.print("X");
          break;

  case 102: // C
          Serial.print("C");
          break;

  case 103: // V
          Serial.print("V");
          break;

  case 104: // B
          Serial.print("B");
          break;

  case 105: // N
          Serial.print("N");
          break;

  case 106: // M
          Serial.print("M");
          break;

  case 107: // ,
          Serial.print(",");
          break;

  case 108: // .
          Serial.print(".");
          break;

  case 109: // /
          Serial.print("/");
          break;

  case 110: // Shift_R
          Serial.print("Shift_R");
          break;

  case 47: // R6/KP_Mult
          Serial.print("R6/KP_Mult");
          break;

  case 120: // Meta_L
          Serial.print("Meta_L");
          break;

  case 121: // SpaceBar
          Serial.print("SpaceBar");
          break;

  case 119: // CapsLock
          Serial.print("CapsLock");
          break;

  case 5: // F1
          Serial.print("F1");
          break;

  case 6: // F2
          Serial.print("F2");
          break;

  case 8: // F3
          Serial.print("F3");
          break;

  case 10: // F4
          Serial.print("F4");
          break;

  case 12: // F5
          Serial.print("F5");
          break;

  case 14: // F6
          Serial.print("F6");
          break;

  case 16: // F7
          Serial.print("F7");
          break;

  case 17: // F8
          Serial.print("F8");
          break;

  case 18: // F9
          Serial.print("F9");
          break;

  case 7: // F10
          Serial.print("F10");
          break;

  case 68: // R7/KP_7/Home
          Serial.print("R7/KP_7/Home");
          break;

  case 69: // R8/KP_8/Up
          Serial.print("R8/KP_8/Up");
          break;

  case 70: // R9/KP_9/PgUp
          Serial.print("R9/KP_9/PgUp");
          break;

  case 71: // KP_Minus
          Serial.print("KP_Minus");
          break;

  case 91: // R10/KP_4/Left
          Serial.print("R10/KP_4/Left");
          break;

  case 92: // R11/KP_5/Center
          Serial.print("R11/KP_5/Center");
          break;

  case 93: // R12/KP_6/Right
          Serial.print("R12/KP_6/Right");
          break;

  case 125: // KP_Add
          Serial.print("KP_Add");
          break;

  case 112: // R13/KP_1/End
          Serial.print("R13/KP_1/End");
          break;

  case 113: // R14/KP_2/Down
          Serial.print("R14/KP_2/Down");
          break;

  case 114: // R15/KP_3/PgDn
          Serial.print("R15/KP_3/PgDn");
          break;

  case 94: // KP_0/KP_Insert
          Serial.print("KP_0/KP_Insert");
          break;

  case 50: // KP_./KP_Delete
          Serial.print("KP_./KP_Delete");
          break;

  case 9: // F11
          Serial.print("F11");
          break;

  case 11: // F12
          Serial.print("F12");
          break;

  case 90: // KP_Enter
          Serial.print("KP_Enter");
          break;

  case 46: // R5/KP_Div
          Serial.print("R5/KP_Div");
          break;

  case 122: // Meta_R
          Serial.print("Meta_R");
          break;

  case 52: // T5_Home
          Serial.print("T5_Home");
          break;

  case 20: // T5_Up
          Serial.print("T5_Up");
          break;

  case 96: // T5_PgUp
          Serial.print("T5_PgUp");
          break;

  case 24: // T5_Left
          Serial.print("T5_Left");
          break;

  case 28: // T5_Right
          Serial.print("T5_Right");
          break;

  case 74: // T5_End
          Serial.print("T5_End");
          break;

  case 27: // T5_Down
          Serial.print("T5_Down");
          break;

  case 123: // T5_PgDn
          Serial.print("T5_PgDn");
          break;

  case 44: // T5_Insert
          Serial.print("T5_Insert");
          break;

  case 66: // Delete
          Serial.print("Delete");
          break;

  case 19: // Alt_L
          Serial.print("Alt_L");
          break;
 }        
}

