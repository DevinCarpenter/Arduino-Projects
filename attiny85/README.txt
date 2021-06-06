***
*** --- ATTINY W/ARDUINO UNO HOW-TO ---
***			
*** Full working preparation source: https://www.youtube.com/watch?v=Z_MhVSlMZI8
***
*** Arduino IDE version 1.8.13 confirmed working
***
*** Related info and links can be found at the end of this readme
***
***


  ---------- First Time IDE ready-to-upload steps: ----------

  Part 1:
    A. Open Arduino IDE -> File -> Examples -> ArduinoISP -> ArduinoISP
    B. Make sure Arduino UNO is plugged in and is selected under Tools -> Board
    C. Make sure the ATtiny85 wiring is NOT connected to the arduino
    D. Upload ArduinoISP sketch example.
    E. If upload successful, you will see 'avrdude done. Thank you.'
       - The Arduino UNO is now a programmer A.K.A ISP (In-System Programmer)

  Part 2:
    A. Open Arduino IDE -> File -> Preferences
    B. Paste 'http://drazzy.com/package_drazzy.com_index.json' in 'Additional Boards Manager URLs'
    C. Close Preferences
    D. Open Arduino IDE -> Tools -> Board -> Boards Manager
    E. Install 'ATTinyCore' package by Spence Konde
    F. Close Boards Manager
    - ATTinyCore library now installed and let's your Arduino as ISP upload to ATtiny chips.

  Part 3:
    A. Open Arduino IDE -> Tools -> Board -> ATTinyCore -> ATtiny25/45/85 (no bootloader)
    B. Open Arduino IDE -> Tools -> Chip -> ATtiny85
    C. Open Arduino IDE -> Tools -> Clock Source -> 8 MHz (internal)
    D. Open Arduino IDE -> Tools -> Programmer -> Arduino as ISP
    E. If this is a new ATtiny85 that you have not burned a bootloader - you must do that:
	- Open Arduino IDE -> Tools - Burn Bootloader
    - Arduino IDE has now set the initial fuses (w/bootloader) on the ATtiny and is ready to upload code

  Part 4:
    A. Make sure board is plugged in
    B. Make sure ATtiny wiring is plugged in and correct for programming ATtiny85 with Arduino UNO
    C. Open a sketch and upload - such as Blink.
    - If you experience issues - refer to ATTiny Github (Link at bottom)



  ---------- Returning to ATtiny chips set-up steps: ---------- 

  Part 1:
    A. Open Arduino IDE -> File -> Examples -> ArduinoISP -> ArduinoISP
    B. Make sure Arduino UNO is plugged in and is selected under Tools -> Board
    C. Make sure the ATtiny85 wiring is NOT connected to the arduino
    D. Upload ArduinoISP sketch example.
    E. If upload successful, you will see 'avrdude done. Thank you.'
       - The Arduino UNO is now a programmer A.K.A ISP (In-System Programmer)

  Part 2:
    A. Open Arduino IDE -> Tools -> Board -> ATTinyCore -> ATtiny25/45/85 (no bootloader)
    B. Open Arduino IDE -> Tools -> Chip -> ATtiny85
    C. Open Arduino IDE -> Tools -> Clock Source -> 8 MHz (internal)
    D. Open Arduino IDE -> Tools -> Programmer -> Arduino as ISP
    E. If this is a new ATtiny85 that you have not burned a bootloader - you must do that:
	- Open Arduino IDE -> Tools - Burn Bootloader
    - Arduino IDE has now set the initial fuses (w/bootloader) on the ATtiny and is ready to upload code

  Part 3:
    A. Make sure board is plugged in
    B. Make sure wiring is correct for programming ATtiny85 with Arduino UNO
    C. Open a sketch and upload - such as Blink.




  ---------- Other related information: ----------

  - AVR is a family of microcontrollers developed since 1996 by Atmel
  - ISP means In-System Programmer. Its a controller used to program controllers
  - The 'AT' in ATtiny stands for Atmel.
  - AVRDUDE (AVR Downloader/UploaDEr) is software for programming Atmel AVR Microcontrollers



  ---------- Links: ----------

  - ATtiny85 Pinout: https://github.com/SpenceKonde/ATTinyCore#attiny254585
  - Arduino ATTinyCore library github: https://github.com/SpenceKonde/ATTinyCore
  - Arduino as ISP article: https://www.arduino.cc/en/Tutorial/BuiltInExamples/ArduinoISP
  - HS-300 Servo Doc: https://servodatabase.com/servo/hitec/hs-300
