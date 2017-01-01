# USB-to-Sun Keyboard Adapter using Arduino Micro

It's my firm belief that the best keyboard in history is the Sun Type 5 UNIX Layout.  It big, 
heavy, chunky, blocky, and feels wonderful to me.  What's more?  It's _the_ UNIX keyboard and
the first keyboard I ever fell in love with.  Sadly, the Sun Type 5 only works with Sun workstations.  
The Type 6 keyboard was available with USB, and thats the keyboard I use every day, but it was sleaked 
down from the chunky glory that was the Type 5.  The Type 7 was something of a middle-ground, the 
blocky figure of the Type 5 but it was made with cheap plastics and lacked the heaft of the Type 5.

So, for the last 10+ years I've had a dream of converting Sun Type 5 to USB so I can live the dream.
Commercially available adapters have been on the market forever, but they typically cost $150+, outside
of my budget.  Some adventurous souls have created their own adapters, but they seemed overly complicated
given the task.  What I _really_ wanted was to create my own, simple, afordable adapter.

Last month I came across an Adafruit tutorial that rekindled my old desire: 
[USB NeXT Keyboard with an Arduino Micro](https://learn.adafruit.com/usb-next-keyboard-with-arduino-micro/overview).  
The links provided happened to include the pin-out of the Sun Type 4/5/6 keyboards and some pointers on how 
to build the adapter.  So I found the right plug on [Mouser](http://www.mouser.com/ProductDetail/CUI-Inc/MD-80PL100/)
and on New Years Eve got to hacking on it.  New Years day I had a working Sun Type 5 on my MacBook!

# How to Build

You will require:

* An Arduino based on the Atmel 32u4 chip, these are required by the [Arduino Mouse & Keyboard libraries](https://www.arduino.cc/en/Reference/MouseKeyboard) 
which you'll need for the Arduino to act as a keyboard adapter
* An [MD-80PL100](http://www.mouser.com/ProductDetail/CUI-Inc/MD-80PL100/) Mini-Din 8a (female) panel connector
* A Sun Type 5 Keyboard! (UNIX Layout preferably!)





