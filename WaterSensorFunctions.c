/*
 * File:   WaterSensorFunctions.c
 * Author: tbwhi
 *
 * Created on March 14, 2023, 10:22 AM
 */


#include <avr/io.h>
#include <stdio.h>
#include "WaterSensorHeader.h"


void watersensor_setup(){
    PORTA.DIRSET = 0b00000100; //set A2 to be output --NOTE CHANGE THIS COMPATIBLE LCD cant use any C pins
    PORTD.DIRCLR = 0b0000100; //set D2 to be input -- this line literally does nothing im confused
    
    // Enable global interrupts.
    SREG = 0b10000000; //interrupt can occur
    AC0.CTRLA = 0b00000111; //enables ac and selects large hystersis
    AC0.MUXCTRL = 0b00000011; //selects input signal to negative input DAC reference  
    VREF.ACREF = 0b00000101; //sets Vdd as reference
    AC0.DACREF = 0b01010101; //sets threshold to about 1V (dacref = 85 with Vdd as 3.0)  
    AC0.INTCTRL = 0b00000001; //enables AC interrupt (enables interrupt triggered when bit in ACn.STATUS reg is set)
 }
