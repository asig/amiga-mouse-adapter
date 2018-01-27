# amiga-mouse-adapter

This is a simple small adapter that transforms your Amiga joystick signals
into movement signals of an Amiga mouse.

Very handy if your trusty old tank mouse seems to be broken, and you need
a mouse _right now_ on a Saturday night, but you can live without a right
mouse button.

# Hardware
All you need is:
- a microcontroller running on +5 VDC with 10 digital I/O pins. I'm using
  an Arduino Pro Mini clone with an Atmel ATmega328 (5V, 16 MHz)
- a male DE-9 (D-sub 9) connector
- a female DE-9 connector
- a soldering iron

# Setup
1) Connect the male DE-9 connector to the microcontroller. See the "Input pins"
   definitions in code. You only need the DE-9 pins 1 - 4 (UP, DOWN, LEFT, 
   RIGHT), 6 (FIRE), and 8 (GND).
2) Connect the female DE-9 connector to the microcontroller. See the "Output
   pins" definitions in the code. You need the same  DE-9 pins, and in addition
   pin 7 (+5VDC), as this will power your microcontroller
3) Compile and upload the sketch.

# Usage
Just plug the adapter between your Amiga and your joystick. Then use your 
joystick to move the mouse cursor.

# Future improvements
A gazillion of people already did this, and you can buy it on ebay, but I 
still plan to turn this into a PS/2 mouse adapter anyway, somewhen in the
future.