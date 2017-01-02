# USB-to-Sun Keyboard Adapter using Arduino Micro

It's my firm belief that the best keyboard in history is the Sun Type 5 UNIX Layout.  It big, heavy, chunky, blocky, and feels wonderful to me.  What's more?  It's _the_ UNIX keyboard and the first keyboard I ever fell in love with.  Sadly, the Sun Type 5 only works with Sun workstations.  

The Type 6 keyboard was available with USB, and thats the keyboard I use every day, but it was sleaked down from the chunky glory that was the Type 5.  The Type 7 was something of a middle-ground, the blocky figure of the Type 5 but it was made with cheap plastics and lacked the heaft of the Type 5.

So, for the last 10+ years I've had a dream of converting Sun Type 5 to USB so I can live the dream. Commercially available adapters have been on the market forever, but they typically cost $150+, outside
of my budget.  Some adventurous souls have created their own adapters, but they seemed overly complicated given the task.  What I _really_ wanted was to create my own, simple, affordable adapter.

Last month I came across an Adafruit tutorial that rekindled my old desire:
[USB NeXT Keyboard with an Arduino Micro](https://learn.adafruit.com/usb-next-keyboard-with-arduino-micro/overview).  The links provided happened to include the pin-out of the Sun Type 4/5/6 keyboards and some pointers on how
to build the adapter.  So I found the right plug on [Mouser](http://www.mouser.com/ProductDetail/CUI-Inc/MD-80PL100/)
and on New Years Eve got to hacking on it.  New Years day I had a working Sun Type 5 on my MacBook!

# How to Build

You will require:

* An Arduino based on the Atmel 32u4 chip, these are required by the [Arduino Mouse & Keyboard libraries](https://www.arduino.cc/en/Reference/MouseKeyboard)
which you'll need for the Arduino to act as a keyboard adapter
* A USB Type A to USB Micro B cable to attach the Arduino to your computer
* An [MD-80PL100](http://www.mouser.com/ProductDetail/CUI-Inc/MD-80PL100/) Mini-Din 8a (female) panel connector
* A Sun Type 5 Keyboard! (UNIX Layout preferably!)

The Sun keyboard uses a Mini-Din 8a connector.  Thanks to Alexander Kurz you can find the [Sun Type 4/5/6 Pinout](http://www.kbdbabel.org/conn/index.html) on kbdbabel.org:

![Keyboard Pinout](http://www.kbdbabel.org/conn/kbd_connector_sun456.png)

You'll notice that they keyboard has its own Vcc +5v & Ground as well as a "from keyboard" and "to keyboard".  You also have 3 more wires providing Vcc +5V & Ground plus a single read line for the mouse!   (We'll ignore the mouse for now).

Lets connect to our Arduino!  If you buy the MD-80PL100 I recommended above ([PDF datasheet](http://www.mouser.com/ds/2/670/md-xxpl100-series-516094.pdf)]), the write mapping will be:

| Keyboard Plug  |         Arduino |
|----------------|-----------------|
| Pin 2 (White)  | GND             |
| Pin 8 (Red)    | +5V             |
| Pin 6 (Yellow) | D10 (Serial RX) |
| Pin 5 (Green)  | D11 (Serial TX) |

Wire it up and then you just need to upload the sketch!

# Packaging Ideas

If you are just playing around with a Sun keyboard, build it on a breadboard and then reclaim the parts for other projects.... but if you want to build a perminant solution, read on.

There are several ways you can package this solution.  As of January 2017 there are no Arduiono Micro's sold without headers.  The knock-off Micro's on Amazon all have bad reviews, so I'm avoiding them.  You can either de-solder the headers on a genuine Micro or use snips to clip off the leads for packaging.

One idea is to follow Adafruits favorite pattern and use an Altiods tin like they did for their [NeXT Keyboard adapter](https://learn.adafruit.com/usb-next-keyboard-with-arduino-micro/wiring).

Another option is to perminantly build this adapter into a Sun keyboard.  If you open the case of the keyboard you'll find the circuit board on one side but a lot of extra room on the other.  Using non-conductive epoxy or foam tape (such as 3M VHB Tape RP32) you could mount the Arduino right inside, exposing only the USB cable.  If you do this and are willing to damage the keyboard perminantly, you could cut off the cable and splice (or de-solder it completely), connecting directly to the Arduino bypassing the Mini-Din connector completely!

# How the Keyboard and Software Works

This solution is gloriously simple!  The simplicity is thanks to the capabilities of the Arduino hardware/software and the cleverness of Sun engineers.

The Sun Keyboard is actually a 1200 baud serial device.  Seriuosly.  That sounds odd but is actually wonderful because the Arduino can easily interface with it using the [Serial Library](https://www.arduino.cc/en/Reference/Serial).  We can also use the Arduino [Keyboard/Mouse Library](https://www.arduino.cc/en/Reference/MouseKeyboard) to write to the computer.  Therefore, all we need to do is read from the serial output of the keyboard, translate each key from the Sun scancode to the ASCII equivilent and then write the ASCII to our computer as keyboard input!  

By using the Arduino Serial Monitor and a simple sketch to listen, we can see what they keyboard is sending.  Press "a" on the keyboard and we get the following (decimal) output to the monitor:

```
77
-51
127
```

After some playing around, you'll realize that the 3 values send by the keyboard have 3 meanings represending different actions:

1. **77**: 77 is the code representing the "a" key being pressed down
2. **-51**: This indicates the key being released (key up), but which key?  Add this value to 128 to determine the key!  128-51=77, so the "a" key is being released.  _Clever right!?!_
3. **127**: This code is sent when no other key is being pressed, it is the "all clear" message.

You can verify this all by pressing and holding "a", then pressing and holding "b", then "c", and then release each key one at a time.  You'll clearly see the key downs, key ups, and releases.  

It just so happens that these map perfectly to our Arduino library!

In **SunKeyboard-to-USB/sun_keyboard_map.h** I created an array mapping the Sun scancode (as the array index) to the equivilent ASCII charactor.  You'll notice several keys map to "0" because they aren't supported by the Keyboard library (or PC's for that matter).  By messing with this array you can re-map keys as you wish (such as making Caps Locks Control for PC Layout).

Once you have the Sun to ASCII map worked out, everything is simple!  We listen on Serial for input.  If we get a number between 1 and 126 we look it up in the array and then pass the result (ASCII) to Keyboard.press().  If we get a number less than 0 we know this is a key-up event, so we add to 128 to find the key which we then lookup in the array and pass to Keyboard.release().  Finally, if we get 127 as input, we know that no keys are being pressed, so we send Keyboard.releaseAll()!

Couldn't be simpler.

## Bonus Features

The Keyboard has a speaker built in and you can enable a "bell" (annoying!) and "key chirp".  I have mapped these to the top-right 4 keys: 

* Mute Key: Disable Chirp Mode
* Decrease Volume Key: Enable Chirp Mode
* Increase Volume Key: Turn on Bell (constant sound)
* Power Key: Turn off Bell

## What doesn't work (yet)

* Scroll Lock and Compose don't function by design; there is no practical use for them and don't see a reason to add the 10 lines of logic
* I force Number lock on and you can not toggle it (may fix in the future)
* All Sun specific keys do not work (but you can remap them how you wish), this is a limitation of the way the Arduino Keyboard library emulates the keyboard.  I may find a fix for it in the future, but not planned.
* The passthrough mouse doesn't work, but I didn't like it anyway.. may or may not add in the future

# Acknowledgements

* Arduino.cc
* Adafruit
* Alexander Kurz's awesome Keyboard Pin-outs
