HD44780 - 4-bit
===============
Header and source for an LCD named: HD44780

The following illustrates the setup used in this example.
 _________________
|              VSS|-> Gnd
|              VDD|-> 5V+
|               V0|-> Middle pin on a Potentiometer
|               VS|-> MCUs pin 4 on port C
|               RW|-> Gnd
|                E|-> MCUs pin 5 on port C
|               D0|
|       LCD     D1|
|               D2|
|               D3|
|               D4|-> MCUs pin 0 on port C
|               D5|-> MCUs pin 1 on port C
|               D6|-> MCUs pin 2 on port C
|               D7|-> MCUs pin 3 on port C
|                A|-> 5V+ or middle pin on a Potentiometer
|                K|-> Gnd
|_________________|

So far tested on: Atmeaga8-16PU