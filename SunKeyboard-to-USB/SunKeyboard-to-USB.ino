/*
 * USB Adapter for Sun Type 5 Keyboard
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

#include <Keyboard.h>
#include <SoftwareSerial.h>
#include "sun_keyboard_map.h"


//Software serial for Sun KBD
SoftwareSerial sunSerial(10, 11, true);


void setup() {
  Serial.begin(1200);	// Normal serial for Serial Monitor Debugging
  sunSerial.begin(1200);	// Serial Connection to Sun Keyboard

  // Initialize USB Keyboard Interface
  dddsssKeyboard.begin();
}


void loop() {
  char c = sunSerial.read();
  if (c == 1){	// Stop Key terminates keyboard
    Serial.println("STOP key pressed, terminating keyboard.");
    Keyboard.end();
  }
  if (c == 3){
    Serial.println("AGAIN key pressed, resuming keyboard.");
    Keyboard.begin();
  }
  if (c != 0xFFFFFFFF) {
    translateKey(c);
  }
}


void translateKey(int key){

 if (key < 0) {	
  key += 128;
  Serial.print("Key Up: "); Serial.println(sun_to_ascii[key]);
  Keyboard.release(sun_to_ascii[key]);
 } else if (key == 127) {
  Serial.print("All Keys Released");
  Keyboard.releaseAll();
 } else {
  Serial.print("Key Down: "); Serial.println(sun_to_ascii[key]);
  Keyboard.press(sun_to_ascii[key]);
 }
}
