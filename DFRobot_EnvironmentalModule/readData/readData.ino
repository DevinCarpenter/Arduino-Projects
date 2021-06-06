/*!
 * @file readData.ino
 * @brief Read the concentration of carbon dioxide and TVOC
 * @n Experiment phenomenon: read data every 0.5s, and print it out on serial port. 
 *
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [LuoYufeng](yufeng.luo@dfrobot.com)
 * @version  V0.1
 * @date  2019-07-19
 * @get from https://www.dfrobot.com
 * @url https://github.com/DFRobot/DFRobot_CCS811
 * 
 * referernced https://wiki.dfrobot.com/Multi_function_Environmental_Module_CCS811_BME280_SKU_SEN0335
 */
#include "DFRobot_CCS811.h"

/*
 * IIC address default 0x5A, the address becomes 0x5B if the ADDR_SEL is soldered.
 */
//DFRobot_CCS811 CCS811(&Wire, /*IIC_ADDRESS=*/0x5A);
DFRobot_CCS811 CCS811;

void setup(void)
{
    Serial.begin(115200);
    /*Wait for the chip to be initialized completely, and then exit*/
    while(CCS811.begin() != 0){
        Serial.println("failed to init chip, please check if the chip connection is fine");
        delay(1000);
    }
}
void loop() {
    if(CCS811.checkDataReady() == true){
        Serial.print("CO2: ");
        Serial.print(CCS811.getCO2PPM());
        Serial.print("ppm, TVOC: ");
        Serial.print(CCS811.getTVOCPPB());
        Serial.println("ppb");
        
    } else {
        Serial.println("Data is not ready!");
    }
    /*!
     * @brief Set baseline
     * @param get from getBaseline.ino
     */
     //Baseline attained 5/14/2021 @ 4:00 a.m. 0x6468 Env. Module Com 3 Uno
     //Baseline attained 5/14/2021 @ 4:30 p.m. 0x146A Env. Module Com 3 Uno
     //Baseline attained 5/14/2021 @ 7:00 p.m. 0x2469 Env. Module Com 3 Uno
     //Baseline attained 5/14/2021 @ 8:50 p.m. 0xAAB7 Air Q. Sensor Com 8 Uno
     //Baseline attained 5/14/2021 @ 4:50 a.m. 0x046E Env. Module Com 3 Uno
     //Baseline attained 5/14/2021 @ 4:50 a.m. 0x05B9 Air Q. Sensor Com 8 Uno
    CCS811.writeBaseLine(0x046E);
    //delay cannot be less than measurement cycle
    delay(1000);
}
