// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

/**
* Wiring Ref 1: https://www.arduino.cc/en/Guide/MKRCANShield
* Wiring Ref 2: https://github.com/sandeepmistry/arduino-CAN
* OBD2 Ref: https://github.com/sandeepmistry/arduino-OBD2

* Use arduino ISCP header to connect miso/mosi/sck
* SPI Ref: https://www.arduino.cc/en/Reference/SPI
* 
* Other project example ref: https://www.element14.com/community/community/arduino/blog/2019/06/18/arduino-mkr-can-shield-review
*
*
*/

#include <CAN.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("CAN Receiver");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(250E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
  //CAN.setPins(9, 2);
}

void loop() {
  // try to parse packet
  int packetSize = CAN.parsePacket();

  if (packetSize) {
    // received a packet
    Serial.print("Received ");

    if (CAN.packetExtended()) {
      Serial.print("extended ");
    }

    if (CAN.packetRtr()) {
      // Remote transmission request, packet contains no data
      Serial.print("RTR ");
    }

    Serial.print("packet with id 0x");
    Serial.print(CAN.packetId(), HEX);

    if (CAN.packetRtr()) {
      Serial.print(" and requested length ");
      Serial.println(CAN.packetDlc());
    } else {
      Serial.print(" and length ");
      Serial.println(packetSize);

      // only print packet data for non-RTR packets
      while (CAN.available()) {
        Serial.print((char)CAN.read());
      }
      Serial.println();
    }

    Serial.println();
  }
}
