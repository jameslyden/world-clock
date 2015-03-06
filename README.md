WorldClock
==========

The WorldClock is a multi-timezone clock designed to display the local date and
time, along with UTC and multiple other user-defined timezones.

Display Characteristics
-----------------------
WorldClock is currently targeting a hardware configuration of dual 16x2 LCDs,
with a layout that can display four timezones at a time. See layouts.md for
diagrams of the primary and alternate display modes that provide the 4-zone
displays.

Hardware Requirements
---------------------
As currently designed, WorldClock requires the following minimum set of hardware:
* 5V Arduino-compatible microcontroller (tested on Uno R3 and Mini Pro)
* Two 16-line, two-row LCDs compatible with SerLCD commands
* DS1302-compatible real-time clock
* 5 momentary pushbuttons

In the future, the hardware requirements may be made more flexible through a
number of new features, such as replacing RTC input with an internal timer-driven
interrupt and manual date/time settings. Also, the control code is being written
for maximum flexibility in the total quantity of time zones, as well as easy
tailoring of the display layouts.
