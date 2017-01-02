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

boolean NUM_LOCK_ON = false;  // led bitfield xxx1 (1)
boolean CAPS_LOCK_ON = false; // led bitfield 1xxx (8)

byte led_cmd[2] = { 0x0E, 0x01 };  // Used for sending the 2 byte commands to the keyboard

void setup() {
  Serial.begin(1200);	        // Normal serial for Serial Monitor Debugging
  sunSerial.begin(1200);	// Serial Connection to Sun Keyboard
 
  Keyboard.begin();             // Initialize USB Keyboard Interface
  
  sunSerial.write(led_cmd, 2);  // Enable Number Lock by Default
}


void loop() {
  char c = sunSerial.read();
  
  if (c != 0xFFFFFFFF) {
   switch(c) {
    case 45:  sunSerial.write(CMD_DISABLE_CLICK); break;     // Mute Key to Disable Click Sound
    case 2:   sunSerial.write(CMD_ENABLE_CLICK); break;      // Decr Vol Key to Enable Click Sound
    case 4:   sunSerial.write(CMD_ENABLE_BELL); break;       // Incr Vol to Enable Bell
    case 48:  sunSerial.write(CMD_DISABLE_BELL); break;      // Power Key to Disable Bell 
    case 98:  break;                                         // Ignore NumLock
    case 119: if (!CAPS_LOCK_ON) {                           // Caps Lock Toggle
                CAPS_LOCK_ON = true;
                led_cmd[1] += 8;
                sunSerial.write(led_cmd, 2);
              } else {
                CAPS_LOCK_ON = false;
                led_cmd[1] -= 8;
                sunSerial.write(led_cmd, 2);                 
              }
    default: outputKey(c); break;
   }
  }
}


void outputKey(int key){

 if (key < 0) {	
  key += 128;
  Serial.print("Key Up: "); Serial.println(sun_to_ascii[key]);
  Keyboard.release(sun_to_ascii[key]);
 } else if (key == 127) {
  Serial.println("All Keys Released");
  Keyboard.releaseAll();
 } else {
  Serial.print("Key Down: "); Serial.println(sun_to_ascii[key]);
  Keyboard.press(sun_to_ascii[key]);
 }
}



