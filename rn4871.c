/*
 * File:   rn4871.c
 * Author: karam
 *
 * Created on March 12, 2023, 9:52 AM
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "rn481.h"

int configureUSART0(){
     // Disables global interrupts.
    SREG = 0b00000000;
   
    CCP = 0xd8;
    CLKCTRL.OSCHFCTRLA = 0b00010100;
    while( CLKCTRL.MCLKSTATUS & 0b00000001 ){
        ;
    }
    //Baud frequency is 115200 hz with Baud then being 277
    USART0.BAUDL =0b01010101;
    USART0.BAUDH =0b11010000;
    
    
    
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