# Simple-Glider

A ESP 3 channel (only using 2) glider meant to be easy to build.

## Glider
The glider was designed to be a foam and 3d print hybrid. The templates are used to trace nets onto foam board that is then cut out. The fuselage is reinforced using 3d printed cubes. The cockpit is fully 3d printed.

## Transmitter
Using a ESP32 and single Joystick. The transmitter takes the analog input of the joystick and maps it from 0 to 255 for PWM. It will then transmit to the receiver.

## Receiver
Using a ESP8266. The receiver will convert the received value to a PWM output for the servos.

## Building the plane
The 3D printed templates allow for the plan to easily traced on foam board that can then be cut out.

Lengths, mm:
- Fuselage: 510, 20 will be used to connect to cockpit
- Wing:     600
- spar:     660
- cockpit:  100-130, depending on your electronics
