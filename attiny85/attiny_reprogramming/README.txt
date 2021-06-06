Re-programming what the ATtiny85's pins do is incredibly useful for getting all 6 pins
(excluding VCC/GND) to actually IO. Pin 1 of the ATtiny85 is a reset pin so that is
what needs to be reprogrammed.

ATtiny pinout: https://github.com/SpenceKonde/ATTinyCore/blob/master/avr/extras/Pinout_x5.jpg
ATtiny GPIO guide: https://www.gadgetronicx.com/attiny85-microcontroller-tutorial-gpio-output/
ATtiny reprogramming GPIO guide: https://www.youtube.com/watch?v=yAT_TdD6nL0

ATtiny has:
PWM on pins PB0, PB1 and PB4. (physical pin locations 5,6 and 3 respectively)
ADC (Analog to Digital Converter) on pins PB2, PB3, PB4 and PB5 (physical pins 7, 3, 2 and 1 respectively)




