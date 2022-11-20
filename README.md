# ArduRPM
using my ArduPSU board as a RPM counter for my minilathe; so far the setup has been successful, but the code for the counter doesn't go back to zero when the lathe spindle stops (should display "0 RPM"). 
I am working on some more solid code for this..
This code is an early version; the later version currently in the counter is buried somewhere on the workshop lappie...
It appears that the conventional Arduino libraries and methods using timers and interrupts have issues at slow speeds and high speeds..next approach is to do it in AVR code directly, rather than Arduino code.
Still the 3D printed case has worked out quite well, with a RJ style socket for the sensor head and a DC power socket for the 5V needed to run the unit.
The ARDUpsu board is being reworked to allow other applications on the atMEGA328 with the 8x2 OLED display..
