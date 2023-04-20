/*
 * File:   AVRcommunication.c
 * Author: karam
 *
 * Created on March 30, 2023, 8:09 PM
 */


/*
 * File:   rn4871.c
 * Author: karam
 *
 * Created on March 12, 2023, 9:52 AM
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "AVRcommunication.h"


int configureUSART1(){
     // Disables global interrupts.
    SREG = 0b00000000;
   
    CCP = 0xd8;
    CLKCTRL.OSCHFCTRLA = 0b00010100;
    while( CLKCTRL.MCLKSTATUS & 0b00000001 ){
        ;
    }
    //Baud frequency is 115200 hz with Baud then being 277
    USART1.BAUDL =0b01010101;
    USART1.BAUDH =0b11010000;
    
    
    
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