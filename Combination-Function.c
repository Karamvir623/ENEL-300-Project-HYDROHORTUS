/*
 * File:   Combination-Functions.c
 * Author: tbwhi
 *
 * Created on March 30, 2023, 10:18 AM
 */

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "rn481.h"
#include "MoistureSensorHeader.h"
#include "LCDHeader.h"
#include "AVRcommunication.h"
#include "WaterSensorHeader.h"
#include "TVremote.h"
#include "RTCHeader.h"
#include "DeviceSettings.h"
#include <stdlib.h>

/*
 * File:   AVRcommunication.c
 * Author: karam
 *
 * Created on March 30, 2023, 8:09 PM
 */
int rtc_setup_BLE(unsigned int time){
    RTC.INTFLAGS |= 0b00000010; //clears flag
    PORTA.DIRSET = 0b00000100; //set PA2 to be output
    CCP = 0xd8; //main clock 
    CLKCTRL.OSC32KCTRLA = 0b10000000; //sets to 32.769 kHz internal oscillator
    
    while(!(CLKCTRL.MCLKSTATUS & CLKCTRL_OSC32KS_bm)){ //stays in loop til clock stable
         ;
     }
    while(RTC.STATUS > 0){ //checks if RTC Status busy
         ;
     }
    RTC.CMP = time; //set compare value to whatever time is
    RTC.PER = time; //selects counter to whatever time is
    RTC.CNT = 0x0000; //initializes count to 0
    RTC.CLKSEL = 0b00000000; //selects 32.769 kHz internal oscillator
    RTC.INTCTRL = 0b00000010; //enables compare match interrupt
    RTC.CTRLA = 0x79; //prescaler RTC clock/32768, RTCEN enables, RUNSTDBY disables
    
    while (RTC.PITSTATUS > 0){ //wait for registers to synchronize
        ;
    }
    RTC.PITINTCTRL = 0x0; //PIT disables  
    while (1) {
        
        if((ADC0.RES <= 409.6))
        {
            return 1;
        }
        if((USART0.STATUS & 0b10000000))
            return 1;
         
         if((PORTF.IN & 0b01000000)==0)
            return 1;
        
        
        if(RTC.INTFLAGS & 0b00000010){ //enters this when we hit the counter value
            return 2;   
  
        }
    }
}

int rtc_setup_ADC(unsigned int time){
    RTC.INTFLAGS |= 0b00000010; //clears flag
    PORTA.DIRSET = 0b00000100; //set PA2 to be output
    CCP = 0xd8; //main clock 
    CLKCTRL.OSC32KCTRLA = 0b10000000; //sets to 32.769 kHz internal oscillator
    
    while(!(CLKCTRL.MCLKSTATUS & CLKCTRL_OSC32KS_bm)){ //stays in loop til clock stable
         ;
     }
    while(RTC.STATUS > 0){ //checks if RTC Status busy
         ;
     }
    RTC.CMP = time; //set compare value to whatever time is
    RTC.PER = time; //selects counter to whatever time is
    RTC.CNT = 0x0000; //initializes count to 0
    RTC.CLKSEL = 0b00000000; //selects 32.769 kHz internal oscillator
    RTC.INTCTRL = 0b00000010; //enables compare match interrupt
    RTC.CTRLA = 0x79; //prescaler RTC clock/32768, RTCEN enables, RUNSTDBY disables
    
    while (RTC.PITSTATUS > 0){ //wait for registers to synchronize
        ;
    }
    RTC.PITINTCTRL = 0x0; //PIT disables  
    while (1) {
        
        if((ADC0.RES <= 2457.6))
            return 1;
        
        if(RTC.INTFLAGS & 0b00000010){ //enters this when we hit the counter value
            return 2;   
  
        }
        if(USART0.STATUS & 0b10000000)
            return 1;
        
          if((PORTF.IN & 0b01000000)==0)
            return 1;
        
        
            
        
    }
}
int rtc_setup_ADC2(unsigned int time){
    RTC.INTFLAGS |= 0b00000010; //clears flag
    PORTA.DIRSET = 0b00000100; //set PA2 to be output
    CCP = 0xd8; //main clock 
    CLKCTRL.OSC32KCTRLA = 0b10000000; //sets to 32.769 kHz internal oscillator
    
    while(!(CLKCTRL.MCLKSTATUS & CLKCTRL_OSC32KS_bm)){ //stays in loop til clock stable
         ;
     }
    while(RTC.STATUS > 0){ //checks if RTC Status busy
         ;
     }
    RTC.CMP = time; //set compare value to whatever time is
    RTC.PER = time; //selects counter to whatever time is
    RTC.CNT = 0x0000; //initializes count to 0
    RTC.CLKSEL = 0b00000000; //selects 32.769 kHz internal oscillator
    RTC.INTCTRL = 0b00000010; //enables compare match interrupt
    RTC.CTRLA = 0x79; //prescaler RTC clock/32768, RTCEN enables, RUNSTDBY disables
    
    while (RTC.PITSTATUS > 0){ //wait for registers to synchronize
        ;
    }
    RTC.PITINTCTRL = 0x0; //PIT disables  
    while (1) {
        
        if((ADC0.RES <= 1638.4))
            return 1;
        if((ADC0.RES >= 2457.6))
                return 1;
        
        if((USART0.STATUS & 0b10000000))
            return 1;
          if((PORTF.IN & 0b01000000)==0)
            return 1;
        
        if(RTC.INTFLAGS & 0b00000010){ //enters this when we hit the counter value
            return 2;   
  
        }
    }
}


void rtc_setup(unsigned int time){
    RTC.INTFLAGS |= 0b00000010; //clears flag
    PORTA.DIRSET = 0b00000100; //set PA2 to be output
    CCP = 0xd8; //main clock 
    CLKCTRL.OSC32KCTRLA = 0b10000000; //sets to 32.769 kHz internal oscillator
    
    while(!(CLKCTRL.MCLKSTATUS & CLKCTRL_OSC32KS_bm)){ //stays in loop til clock stable
         ;
     }
    while(RTC.STATUS > 0){ //checks if RTC Status busy
         ;
     }
    RTC.CMP = time; //set compare value to whatever time is
    RTC.PER = time; //selects counter to whatever time is
    RTC.CNT = 0x0000; //initializes count to 0
    RTC.CLKSEL = 0b00000000; //selects 32.769 kHz internal oscillator
    RTC.INTCTRL = 0b00000010; //enables compare match interrupt
    RTC.CTRLA = 0x79; //prescaler RTC clock/32768, RTCEN enables, RUNSTDBY disables
    
    while (RTC.PITSTATUS > 0){ //wait for registers to synchronize
        ;
    }
    RTC.PITINTCTRL = 0x0; //PIT disables  
    while (1) {
        
        
        
        if(RTC.INTFLAGS & 0b00000010){ //enters this when we hit the counter value
            return;   
  
        }
    }
}

int configureUSART1(){
     // Disables global interrupts.
    SREG = 0b00000000;
   
    CCP = 0xd8;
    CLKCTRL.OSCHFCTRLA = 0b00010100;
    while( CLKCTRL.MCLKSTATUS & 0b00000001 ){
        ;
    }
    //Baud frequency is 115200 hz with Baud then being 277
    USART1.BAUDL =0b00010101;
    USART1.BAUDH =0b00000001;
    
    
    
    // setting the USART to normal mode and Asynchronous
    USART1.CTRLC = 0b00000011;
    // enabling the transmitter and receiver 
    USART1.CTRLB = 0b11000000;
    // enabling the interrupts 
    USART1.CTRLA = 0b11110000; 
            
    // Makes sure that our input is only one direction
    PORTC.DIR = 0b11111101;
    // Enable PA0 as an output pin.
    PORTC.DIRSET = 0b00000001;
    // Enable PA1 as an input pin.
    PORTC.DIRCLR = 0b00000010;
    
    // Enable global interrupts.
    SREG = 0b10000000;
    
    return 1 ;
}






int receiveAOK1(){
    char c[3];
    for(int i = 0; i<2; i++){
        c[i] = receive1();
        
    }
    if((c[0] == 'A') && (c[1] == 'O') && (c[2] == 'K')){
        return 1;
    }
    return 0;            
}




 
 
 void transmit1(char*p){
     for(int i= 0; p[i]!= '\0'; i++){
       if(USART1.STATUS & 0b00100000) { //checks if the data registers are empty and can receive data
             USART1.TXDATAL = p[i];  // sends data to the register 
       }                   
         while(!(USART1.STATUS & 0b01000000))
         {}// waits until all the bits are transmitted 
         USART1.STATUS |= 0b01000000; // clears the flag
         
     }
  
                
 }
 void sendr1(){
     if(USART1.STATUS & 0b00100000) { //checks if the data registers are empty and can receive data
             USART1.TXDATAL = 13;  // sends \r

       } 
     while(!(USART1.STATUS & 0b01000000)); // waits until all the bits are transmitted 
      USART1.STATUS |= 0b01000000; // clears the flag
     
 }
 
 
 char receive1(){
     while(1){
         if((USART1.STATUS & 0b10000000) ){ // checks if anything is received
             return USART1.RXDATAL;
         }
     }  
                 
 }
 
 void receiveword1(char*p, int size){
     while(1){
         for(int i=0; i< 0; i++)
         { 
            while(1){
              if((USART1.STATUS & 0b10000000) ){ // checks if anything is received
                  p[i] = USART1.RXDATAL;
                  break;
              }
              
           }     
         }
     }
 }
 
 
 void microdelay1(unsigned int val){
    // Disables global interrupts.
    SREG = 0b00000000;
    // Set internal clock frequency to 8 MHz.
    CCP = 0xd8;
    CLKCTRL.OSCHFCTRLA = 0b00010100;
    while( CLKCTRL.MCLKSTATUS & 0b00000001 ){
        ;
    }
    // Configure the timer to increment every 2us.
    // - Divide the 8MHz clock by 16.
    TCA0.SINGLE.CTRLA = 0b00001001;
    
    // We will manually check the timer and reset the timer
    // so set the period to its max value to avoid an automatic
    // reset.
    TCA0.SINGLE.PER = 0xffff;
    
    // Set the timer threshold.
    // f= 0.5 MHz and T = 2x10^-6
    // multiplying the period by 1000 gives u 2ms
    unsigned int timerThreshold = (val/2)*1000;
    
    while( TCA0.SINGLE.CNT <= timerThreshold) {
        
                                               }// counts 1000 times      
        TCA0.SINGLE.CNT = 0;
}
void millidelay1(unsigned int val){
    // Disables global interrupts.
    SREG = 0b00000000;
    // Set internal clock frequency to 8 MHz.
    CCP = 0xd8;
    CLKCTRL.OSCHFCTRLA = 0b00010100;
    while( CLKCTRL.MCLKSTATUS & 0b00000001 ){
        ;
    }
    // Configure the timer to increment every 2us.
    // - Divide the 8MHz clock by 16.
    TCA0.SINGLE.CTRLA = 0b00001001;
    
    // We will manually check the timer and reset the timer
    // so set the period to its max value to avoid an automatic
    // reset.
    TCA0.SINGLE.PER = 0xffff;
    
    // Set the timer threshold.
    // f= 0.5 MHz and T = 2x10^-6
    // multiplying the period by 1000 gives u 2ms
    unsigned int timerThreshold = (val/2)*1000000;
    while( TCA0.SINGLE.CNT <= timerThreshold)  {
                                               }// counts 1000 times 
}


int configureUSART0(){
     // Disables global interrupts.
    SREG = 0b00000000;
   
    CCP = 0xd8;
    CLKCTRL.OSCHFCTRLA = 0b00010100;
    while( CLKCTRL.MCLKSTATUS & 0b00000001 ){
        ;
    }
    //Baud frequency is 115200 hz with Baud then being 277
    USART0.BAUDL =0b00010101;
    USART0.BAUDH =0b00000001;
   
    
    
    // setting the USART to normal mode and Asynchronous
    USART0.CTRLC = 0b00000011;
    // enabling the transmitter and receiver 
    USART0.CTRLB = 0b11000000;
    // enabling the interrupts 
    USART0.CTRLA = 0b11110000; 
            
    // Makes sure that our input is only one direction
    PORTA.DIR = 0b11111101;
    // Enable PA0 as an output pin.
    PORTA.DIRSET = 0b00000001;
    // Enable PA1 as an input pin.
    PORTA.DIRCLR = 0b00000010;
    
    // Enable global interrupts.
    SREG = 0b10000000;
    
    return 1;
}




int receiveAOK(){
    char c[3];
    for(int i = 0; i<2; i++){
        c[i] = receive();
        
    }
    if((c[0] == 'A') && (c[1] == 'O') && (c[2] == 'K')){
        return 1;
    }
    return 0;            
}




 
 
 void transmit(char*p){
     for(int i= 0; p[i]!= '\0'; i++){
       if(USART0.STATUS & 0b00100000) { //checks if the data registers are empty and can receive data
             USART0.TXDATAL = p[i];  // sends data to the register 
       }                   
         while(!(USART0.STATUS & 0b01000000))
         {}// waits until all the bits are transmitted 
         USART0.STATUS |= 0b01000000; // clears the flag
         
     }
     if(USART0.STATUS & 0b00100000) { //checks if the data registers are empty and can receive data
             USART0.TXDATAL = '\0';  // sends data to the register 
       }                   
    while(!(USART0.STATUS & 0b01000000))
         {}// waits until all the bits are transmitted 
    USART0.STATUS |= 0b01000000; // clears the flag
                
 }
 void sendr(){
     if(USART0.STATUS & 0b00100000) { //checks if the data registers are empty and can receive data
             USART0.TXDATAL = 13;  // sends \r

       } 
     while(!(USART0.STATUS & 0b01000000)); // waits until all the bits are transmitted 
      USART0.STATUS |= 0b01000000; // clears the flag
     
 }
 
 
 char receive(){
     while(1){
         if((USART0.STATUS & 0b10000000) ){ // checks if anything is received
             return USART0.RXDATAL;
         }
     }  
                 
 }
 
 void receiveword(char*p, int size){
     while(1){
         for(int i=0; i< 0; i++)
         { 
            while(1){
              if((USART0.STATUS & 0b10000000) ){ // checks if anything is received
                  p[i] = USART0.RXDATAL;
                  break;
              }
              
           }     
         }
     }
 }
 
 
 void microdelay(unsigned int val){
    // Disables global interrupts.
    SREG = 0b00000000;
    // Set internal clock frequency to 8 MHz.
    CCP = 0xd8;
    CLKCTRL.OSCHFCTRLA = 0b00010100;
    while( CLKCTRL.MCLKSTATUS & 0b00000001 ){
        ;
    }
    // Configure the timer to increment every 2us.
    // - Divide the 8MHz clock by 16.
    TCA0.SINGLE.CTRLA = 0b00001001;
    
    // We will manually check the timer and reset the timer
    // so set the period to its max value to avoid an automatic
    // reset.
    TCA0.SINGLE.PER = 0xffff;
    
    // Set the timer threshold.
    // f= 0.5 MHz and T = 2x10^-6
    // multiplying the period by 1000 gives u 2ms
    unsigned int timerThreshold = (val/2)*1000;
    
    while( TCA0.SINGLE.CNT <= timerThreshold) {
        
                                               }// counts 1000 times      
        TCA0.SINGLE.CNT = 0;
}
void millidelay(unsigned int val){
    // Disables global interrupts.
    SREG = 0b00000000;
    // Set internal clock frequency to 8 MHz.
    CCP = 0xd8;
    CLKCTRL.OSCHFCTRLA = 0b00010100;
    while( CLKCTRL.MCLKSTATUS & 0b00000001 ){
        ;
    }
    // Configure the timer to increment every 2us.
    // - Divide the 8MHz clock by 16.
    TCA0.SINGLE.CTRLA = 0b00001001;
    
    // We will manually check the timer and reset the timer
    // so set the period to its max value to avoid an automatic
    // reset.
    TCA0.SINGLE.PER = 0xffff;
    
    // Set the timer threshold.
    // f= 0.5 MHz and T = 2x10^-6
    // multiplying the period by 1000 gives u 2ms
    unsigned int timerThreshold = (val/2)*1000000;
    while( TCA0.SINGLE.CNT <= timerThreshold)  {
                                               }// counts 1000 times 
}

void moisturesensor_setup(){
    PORTA.DIRSET = 0b00000100; //set A2 to be output --NOTE CHANGE THIS COMPATIBLE LCD cant use any C pins
    PORTD.DIRCLR = 0b0000100; //set D2 to be input -- this line literally does nothing im confused
    
    // Enable global interrupts.
    SREG = 0b10000000; //interrupt can occur
    AC0.CTRLA = 0b00000111; //enables ac and selects large hystersis
    AC0.MUXCTRL = 0b00000011; //selects input signal to negative input DAC reference  
    VREF.ACREF = 0b00000101; //sets Vdd as reference
    AC0.DACREF = 164; //sets threshold to about 3.2V (dacref = 164)  
    AC0.INTCTRL = 0b00000001; //enables AC interrupt (enables interrupt triggered when bit in ACn.STATUS reg is set)
 }

#ifndef lcd_MicroDelay
#define lcd_MicroDelay { char __x = 1; while(--__x); }
#endif

void lcd_string(char *letter){
    for(int i = 0; letter[i] != '\0'; i++){
        
        //sending character letter[i] 0x61
        PORTA.OUT &= 0b110111111; //RW low -- send data to LCD config
        PORTA.OUT |= 0b01000000; //RS high -- send data to LCD config
        PORTC.OUT = (letter[i] >> 4) & 0xF; //high byte of ascii of letter being sent
        PORTA.OUT |= 0b00010000; //set enable to high
        lcd_MicroDelay; //microdelay 
        PORTA.OUT &= 0b11101111; //set enable to low 

        PORTC.OUT = (letter[i]) & 0xF; //low byte of ascii of letter being sent -- you cant use c4-7 on avr
        PORTA.OUT |= 0b00010000; //set enable to high
        lcd_MicroDelay; //microdelay 
        PORTA.OUT &= 0b11101111; //set enable to low 

        delay; //1 ms delay 
    
        }
    
}



void lcd_setup(){
    PORTC.DIRSET = 0b00001111; //set C0, C1, C2, C3 to be outputs -- C0 = D4, C1 = D5, C2 = D6, C3 = D7
    PORTA.DIRSET = 0b01110000; //set A4, A5, A6 to be outputs -- A4 = E, A5 = RW, A6 = RS
    
    for(int i=0; i<1000; i++){
        delay;
    } //15ms sleep 
    PORTA.OUT &= 0b10001111; //set RS RW E off
    
    //initialization 
    //sending 0x02 to LCD
    PORTA.OUT &= 0b010011111; //RS RW low 
    PORTC.OUT = 0b00000000; //high byte of 0x02//****
    PORTA.OUT |= 0b00010000; //set enable to high
    lcd_MicroDelay; //microdelay 
    PORTA.OUT &= 0b11101111; //set enable to low 
    
    PORTC.OUT = 0b00000010; //low byte of 0x02//****
    PORTA.OUT |= 0b00010000; //set enable to high
    lcd_MicroDelay; //microdelay 
    PORTA.OUT &= 0b11101111; //set enable to low 
    
    delay; //1 ms delay 
    
    //sending 0x28 to LCD -- using 4 bit mode
    PORTA.OUT &= 0b010011111; //RS RW low 
    PORTC.OUT = 0b00000010; //high byte of 0x28//****
    PORTA.OUT |= 0b00010000; //set enable to high
    lcd_MicroDelay; //microdelay 
    PORTA.OUT &= 0b11101111; //set enable to low 
    
    PORTC.OUT = 0b00001000; //low byte of 0x28//****
    PORTA.OUT |= 0b00010000; //set enable to high
    lcd_MicroDelay; //microdelay 
    PORTA.OUT &= 0b11101111; //set enable to low 
    
    delay; //1 ms delay 
    
    clear_lcd();
    
    //sending 0x06 -- incrementing cursor (send a letter writes to one location over)
    PORTA.OUT &= 0b010011111; //RS RW low 
    PORTC.OUT = 0b00000000; //high byte of 0x06//****
    PORTA.OUT |= 0b00010000; //set enable to high
    lcd_MicroDelay; //microdelay 
    PORTA.OUT &= 0b11101111; //set enable to low 
    
    PORTC.OUT = 0b000000110; //low byte of 0x06 //****
    PORTA.OUT |= 0b00010000; //set enable to high
    lcd_MicroDelay; //microdelay 
    PORTA.OUT &= 0b11101111; //set enable to low 
    
    delay; //1 ms delay  
} 

void adc_setup(){
    SREG = 0b10000000; // Enable global interrupts.
    VREF.ADC0REF = 0b10000101; // Set the ADC reference level to VDD.
    ADC0.INTCTRL = 0b00000001; // Enable the ADC interrupt.
    //ADC0.MUXPOS = 0x02; // Select PD2 (AIN2) as the ADC input.
   
    ADC0.CTRLC = 0x00; // Select minimum clock divide. 
    ADC0.CTRLA = 0b00000011; // Select single ended mode, 12 bit resolution and free-running modes.
    ADC0.COMMAND = 0x01; // Start conversion.
    PORTD.DIRCLR = 0b00000100; //set PD2 to be input
}

void clear_lcd(){
    //sending 0x01 -- clearing LCD screen
    PORTA.OUT &= 0b010011111; //RS RW low 
    PORTC.OUT = 0b00000000; //high byte of 0x01//****
    PORTA.OUT |= 0b00010000; //set enable to high
    lcd_MicroDelay; //microdelay 
    PORTA.OUT &= 0b11101111; //set enable to low 
    
    PORTC.OUT = 0b000000001; //low byte of 0x01//****
    PORTA.OUT |= 0b00010000; //set enable to high
    lcd_MicroDelay; //microdelay 
    PORTA.OUT &= 0b11101111; //set enable to low 
    
    delay; //1 ms delay
}

void lcd_single(char character){
    //sending character letter[i] 0x61
    PORTA.OUT &= 0b110111111; //RW low -- send data to LCD config
    PORTA.OUT |= 0b01000000; //RS high -- send data to LCD config
    PORTC.OUT = (character >> 4) & 0xF; //high byte of ascii of letter being sent
    PORTA.OUT |= 0b00010000; //set enable to high
    lcd_MicroDelay; //microdelay 
    PORTA.OUT &= 0b11101111; //set enable to low 

    PORTC.OUT = (character) & 0xF; //low byte of ascii of letter being sent -- you cant use c4-7 on avr
    PORTA.OUT |= 0b00010000; //set enable to high
    lcd_MicroDelay; //microdelay 
    PORTA.OUT &= 0b11101111; //set enable to low 

    delay; //1 ms delay 
}
void watersensor_setup(){
    PORTA.DIRSET = 0b00000100; //set A2 to be output --NOTE CHANGE THIS COMPATIBLE LCD cant use any C pins
    PORTD.DIRCLR = 0b0000100; //set D2 to be input -- this line literally does nothing im confused
    
    // Enable global interrupts.
    SREG = 0b10000000; //interrupt can occur
    AC0.CTRLA = 0b00000111; //enables ac and selects large hystersis
    AC0.MUXCTRL = 0b00000011; //selects input signal to negative input DAC reference  
    VREF.ACREF = 0b00000101; //sets Vdd as reference
    AC0.DACREF = 38.7; //sets threshold to about 1V (dacref = 85 with Vdd as 3.0)  
    AC0.INTCTRL = 0b00000001; //enables AC interrupt (enables interrupt triggered when bit in ACn.STATUS reg is set)
 }
