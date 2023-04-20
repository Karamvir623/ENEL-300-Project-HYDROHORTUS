/*
 * File:   Bluetooth.c
 * Author: karam
 *
 * Created on March 3, 2023, 8:49 PM
 */


#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "rn481.h"
#include "MoistureSensorHeader.h"
#include "LCDHeader.h"
#include "AVRcommunication.h"
#include "WaterSensorHeader.h"
#include "RTCHeader.h"
#include "DeviceSettings.h"
#include <stdlib.h>



char waterout[] ="Water has run out, Refill the supply" ;
int watercheck ;
int waterRefill; 
char avrWaterOut[]= "o";
char w[]="K";

char received[] = "N";

char sendAOK[] = "Successful write";
char sendFail[] ="Failed write, try again";

char status1[] = "The Soil is moist";
char status2[] = "The Soil is not moist. Change your water schedule";

char watering[] ="Watering the Plant based on schedule";

char check[]= "";
char invalid[]="The command you sent is INVALID";

char deviceOn[]="Your device is now ON and ready to water your plant";

char watset[] = "y";
char retset[] ="z";
int set =0;

int main(void){
    
    int l = configureUSART0(); //Tx: PA0 and RX: PA1
    int y = configureUSART1(); // Tx: PC0 and RX: PC1
    // Enable PF6 as an input pin.
    
  
    while(1){
     
      /*if (AC0.STATUS & 0b00010000){
           AC0.STATUS = 0b00000001; 
           if(waterRefill == 1){
           while(1){
                    transmit1(waterReplaced);
                    delay;
                    if((USART1.STATUS & 0b10000000))
                            break;
                    }  
         }
         watercheck =0;
         waterRefill =0;
         */
        if((USART0.STATUS & 0b10000000)) {
                received[0] = receive();
                if(received[0] == '1'){
                    while(1){
                        transmit1(received);
                        delay;
                        if((USART1.STATUS & 0b10000000))
                            break;
                    }
                    delay;
                    check[0] = receive1();
                    if(check[0] == 'Q')
                        transmit(sendAOK);
                    
                         
                    } 
                
                else if(received[0] == '2'){
                   while(1){
                        transmit1(received);
                        delay;
                        if((USART1.STATUS & 0b10000000))
                            break;
                    }
                    check[0] = receive1();
                    if(check[0] == 'Q')
                        transmit(sendAOK);
                        
                }
                else if(received[0] == '3'){
                    while(1){
                        transmit1(received);
                        delay;
                        if((USART1.STATUS & 0b10000000))
                            break;
                    }
                    check[0] = receive1();
                    if(check[0] == 'Q')
                        transmit(sendAOK);
                     
                }
                else if(received[0] == 'h'){
                    while(1){
                        transmit1(received);
                        delay;
                        if((USART1.STATUS & 0b10000000))
                            break;
                    }
                    check[0] = receive1();
                    if(check[0] == 'Q')
                        transmit(sendAOK);
                     
                }
                else if(received[0] == 'm'){
                    while(1){
                        transmit1(received);
                        delay;
                        if((USART1.STATUS & 0b10000000))
                            break;
                    }
                    check[0] = receive1();
                    if(check[0] == 'Q')
                        transmit(sendAOK);
                     
                }
                else if(received[0] == 'l'){
                    while(1){
                        transmit1(received);
                        delay;
                        if((USART1.STATUS & 0b10000000))
                            break;
                    }
                    check[0] = receive1();
                    if(check[0] == 'Q')
                        transmit(sendAOK);
                     
                }
                
                
                
                
                
                else if(received[0] == '4'){
                    while(1){
                        transmit1(received);
                        delay;
                        if((USART1.STATUS & 0b10000000))
                            break;
                    }
                       check[0] = receive1();
                        if(check[0]== 'M'){
                            transmit(status1);
                            
                        }
                        
                        if(check[0] == 'D'){
                            transmit(status2);
                            
                         }
                        
                }
               
                
                else{
                    transmit(invalid);
                } 
    }
        if((USART1.STATUS & 0b10000000)) {
            received[0] = receive1();
            if(received[0] == 'W')
                transmit(watering);
                    
        }
            
     
      
          
        
        
        
        
      /*   
       if((AC0.STATUS & 0b00010000)==0){
           watercheck++;
           waterRefill=0;
           PORTA.OUT &= 0b11111011;
           if(watercheck == 1) 
                transmit(waterout);
           while(1){
                transmit1(avrWaterOut);
               
                if((USART1.STATUS & 0b10000000))
                       break;   
            }  
        }
        
        
        if(AC0.STATUS & 0b00010000){
           PORTA.OUT |= 0b00000100;
           watercheck=0;
           waterRefill++;
           while(1){
               if(waterRefill == 1)
                   break;
                    transmit1(w);
                    if((USART1.STATUS & 0b10000000))
                            break;
                    }  
           AC0.STATUS = 0b00000001;
        }
         */
        /*
        if (AC0.STATUS & 0b00010000){
            PORTA.OUT |= 0b00000100;
            watercheck++;
            waterRefill = 0;
            if(watercheck == 1) 
                transmit(waterout);
            while(1){
                transmit1(avrWaterOut);
                delay;
                if((USART1.STATUS & 0b10000000))
                       break;   
            }  
            AC0.STATUS = 0b00000001;
        }
        else if (!(AC0.STATUS & 0b00010000)){ 
           PORTA.OUT &= 0b11111011;
            watercheck=0;
            while(1){
                if(waterRefill != 0)
                    break;
                transmit1(w);
                
                if((USART1.STATUS & 0b10000000)){
                    waterRefill =1;
                    break;
                    }
        }
            
           
    }
    */
   }   
  }

                
       
             
    
        


   
        
         
      
