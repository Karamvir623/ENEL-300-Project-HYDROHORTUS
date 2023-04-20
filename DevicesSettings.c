/*
 * File:   DevicesSettings.c
 * Author: karam
 *
 * Created on April 6, 2023, 12:06 PM
 */


#include <stdio.h>
#include <stdlib.h>
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


char time[] ="     00:00";
char min;
char min1;
char sec1;
char sec;

char wat[]="  Watering";
int val;
int counter;
char avrWatering[]="W";

char opt1C[] = " 3)Schedule water ";
char opt1B[] = "  2)Water When Dry    ";
char opt1A[] = "  1)Manual Water";

int ADCvalue;
int ADCvalue2;
int ADCvalue3;
int ADCvalue4;
int ADCvalue5;

char soilDry2[] ="  Soil is Dry";

char setting[] = "  Water Setting";
char high[]="   High: 10s";
char med[]= "   Medium: 7s";
char low[]= "   low: 3s";
char ret[]= "    Returning";

int setcheck =0;

char scheduleOption1[] = "  30 seconds ";
char scheduleOption2[] = "  20 seconds ";
char scheduleOption3[] = "  10 seconds ";


int waterSetting(){
    ADC0.MUXPOS = 0x06; // Select PD7 (AIN2) as the ADC input.
    int waterval =1;
    longdelay;
    clear_lcd();
    delay;
    lcd_string(setting);
    rtc_setup(1);
    while(1){
       clear_lcd();
                if (ADC0.RES >= 2457.6) {  
                 lcd_string(high);
                 waterval = 10;
                } 
                else if (ADC0.RES >= 1638.4)  {
                   lcd_string(med);
                   waterval = 6;
                }
                else if (ADC0.RES >= 819.2) {
                    lcd_string(low);
                    waterval = 3;
                }
       
               if((PORTF.IN & 0b01000000)==0){
                 setcheck = 1;
                 clear_lcd();
                 delay;
                 lcd_string(ret);
                 rtc_setup(1);
                 clear_lcd();
                 return waterval;
                }
            
        longdelay;
        }
}





void waterMannualBLE(int watervalue) {
    // Enable PA2 as an output pin.
    PORTA.DIRSET = 0b00000100;
 
    // Enable PF6 as an input pin.
    PORTA.DIRCLR = 0b10001000;
    
   
    while(1){
        if((PORTA.IN & 0b10000000)==0){
            transmit(avrWatering);
            clear_lcd();
            lcd_string(wat);
           PORTA.OUT |= 0b00000100;
           rtc_setup_BLE(watervalue);
           }
        
        longdelay;
        clear_lcd();
        lcd_string(opt1A);
        PORTA.OUT &= 0b11111011;
        if(ADC0.RES <= 409.6){
            ADC0.INTFLAGS = 0b00000001;
            return;
        }
        if(USART0.STATUS & 0b10000000)
            return;
       if((PORTF.IN & 0b01000000)==0)
            return;
            
        
           
       }
            
    }
        
 void waterMannualADC(int watervalue) {
    // Enable PA2 as an output pin.
    PORTA.DIRSET = 0b00000100;
    
    // Enable PF6 as an input pin.
    PORTF.DIRCLR = 0b01000000;
   
       
    if((PORTA.IN & 0b10000000)==0){
            transmit(avrWatering);
            clear_lcd();
            lcd_string(wat);
           PORTA.OUT |= 0b00000100;
           rtc_setup(watervalue);
           clear_lcd();
        }
        PORTA.OUT &= 0b11111011;
      
            
    } 
 
 void soilMoistureADC(int watervalue){
     // Enable PA2 as an output pin.
    PORTA.DIRSET = 0b00000100;
    
    // Enable PF6 as an input pin.
    PORTF.DIRCLR = 0b01000000;
    if(AC0.STATUS & 0b00010000){
       int timeval = rtc_setup_ADC2(5);
        if (timeval == 1)
            return;
        ADC0.INTFLAGS = 0b00000001;
        clear_lcd();
        lcd_string(soilDry2);
        rtc_setup_ADC2(3);
        ADC0.INTFLAGS = 0b00000001;
        transmit(avrWatering);
        clear_lcd();
        lcd_string(wat);
        if((ADC0.RES <= 1638.4)||(ADC0.RES >= 2457.6)) {
            ADC0.INTFLAGS = 0b00000001;
            return;
      }
        PORTA.OUT |= 0b00000100;
        rtc_setup_ADC2(watervalue);
        clear_lcd();
    }
    PORTA.OUT &= 0b11111011;   
     
 }
 
 
 
  void soilMoistureBLE(int watervalue){
     // Enable PA2 as an output pin.
    PORTA.DIRSET = 0b00000100;
    
    while(1){
       if(ADC0.RES <= 409.6){
            ADC0.INTFLAGS = 0b00000001;
            break;
      }
      if(USART0.STATUS & 0b10000000)
            break;
       if((PORTF.IN & 0b01000000)==0)
            break;
       else if(AC0.STATUS & 0b00010000){
        rtc_setup_BLE(5);
        clear_lcd();
        lcd_string(soilDry2);
        rtc_setup_BLE(3);
        clear_lcd();
        lcd_string(wat);
        if(USART0.STATUS & 0b10000000)
            return;
        if((PORTF.IN & 0b01000000)==0)
            break;
        transmit(avrWatering);
        PORTA.OUT |= 0b00000100;
        rtc_setup_BLE(watervalue);
        clear_lcd();
        lcd_string(opt1B);
    }
    PORTA.OUT &= 0b11111011; 
     
   
 
    }
  }
 
 
 
 void scheduleBLE(int watervalue){
     int value;   // 5 minutes
    unsigned int water = 5;    // 15 seconds
    PORTA.DIRSET = 0b00000100;  // set PA2 to be output
    PORTA.OUT &= 0b11111011;    // Solenoid is closed
    char re;
    rtc_setup(1);
   if(USART0.STATUS & 0b10000000)
       re = receive();
   rtc_setup(1);
   if(USART0.STATUS & 0b10000000)
       re = receive();
   rtc_setup(1);
   if(USART0.STATUS & 0b10000000)
       re = receive();
    value = schedulingOptions();
    while (1) {
      if(ADC0.RES <= 409.6){
       ADC0.INTFLAGS = 0b00000001;
            break;
        }
      ADCvalue3 = timerBLE(value);// Wait 5 minutes, Solenoid Closed
      if (ADCvalue3 == 1)
        return;
      if(USART0.STATUS & 0b10000000)
            return;
      if((PORTF.IN & 0b01000000)==0)
            return;
      transmit(avrWatering);
      clear_lcd();
      lcd_string(wat);
      PORTA.OUT |= 0b00000100; // Water plant for 15 seconds
      rtc_setup(watervalue);        // Wait 15 seconds, Solenoid Open
      PORTA.OUT &= 0b11111011; // Close solenoid
    }
    
     
 }
  void scheduleADC(int watervalue, int schedule){
    unsigned int value = 300;   // 5 minutes
    unsigned int water = 5;    // 15 seconds
    PORTA.DIRSET = 0b00000100;  // set PA2 to be output
    PORTA.OUT &= 0b11111011;    // Solenoid is closed
     
    
    ADCvalue2 = timer(schedule);// Wait 5 minutes, Solenoid Closed
    if (ADCvalue2 == 1)
        return;
 
    transmit(avrWatering);
    clear_lcd();
    lcd_string(wat);
    PORTA.OUT |= 0b00000100; // Water plant for 15 seconds
    rtc_setup(watervalue);        // Wait 15 seconds, Solenoid Open
    PORTA.OUT &= 0b11111011; // Close solenoid
    
    
     
 }
  
  int timer(int setTime){
      
      val =1;
      counter =0;
      
     for(int l =0,min1='0';l<6;min1++,l++){
             time[5] = min1;
             
          for(int k=0, min='0'; k<10; min++,k++){
             time[6] = min;
            for(int i=0, sec1='0'; i<6; sec1++,i++){
              time[8] =sec1;    
              for(int j= 0, sec ='0';j<5; sec++, j++ ){
                 time[9]= sec;
                 sec++;
                 longerdelay;
                 clear_lcd();
                 lcd_string(time);
                 ADCvalue = rtc_setup_ADC(val);
                 if (ADCvalue == 1)
                     return 1;
                 counter++;
                 if(counter == (setTime/2)){
                     return 0;
                 }
            }
      

        }
      
                  
       }
      }
        
   
  }   
  
  int timerBLE(int setTime){
      
      val =1;
      counter =0;
      
     for(int l =0,min1='0';l<6;min1++,l++){
             time[5] = min1;
             
          for(int k=0, min='0'; k<6; min++,k++){
             time[6] = min;
            for(int i=0, sec1='0'; i<6; sec1++,i++){
              time[8] =sec1;    
              for(int j= 0, sec ='0';j<5; sec++, j++ ){
                 time[9]= sec;
                 sec++;
                 longerdelay;
                 clear_lcd();
                 lcd_string(time);
                 ADCvalue = rtc_setup_BLE(val);
                 if (ADCvalue == 1)
                     return 1;
                 counter++;
                 if(counter == (setTime/2)){
                     return 0;
                 }
            }
      

        }
      
                  
       }
      }
        
   
  } 
  
  int schedulingOptions(){
      while(1){
         ADC0.MUXPOS = 0x06; // Select PD7 (AIN2) as the ADC input.
         
         if (ADC0.RES >= 2457.6) //option F
        {  
             clear_lcd();
             lcd_string(scheduleOption1);
             if((PORTA.IN & 0b10000000)== 0){
                ADC0.MUXPOS = 0x07;
                return 30; 
             }
                 
        
            
        }
        
       
        
          else if (ADC0.RES >= 1638.4)  //option D
        {   clear_lcd();
             lcd_string(scheduleOption2);
             if((PORTA.IN & 0b10000000)==0)
             {
                 ADC0.MUXPOS = 0x07;
                 return 20;
             }
        }
        
        
        
         else if (ADC0.RES >= 819.2) //option B
        {
             clear_lcd();
             lcd_string(scheduleOption3);
             if((PORTA.IN & 0b10000000)==0){
                ADC0.MUXPOS = 0x07;
                return 10; 
             }   
        }
         if(USART0.STATUS & 0b10000000)
            return 0;
         
        
        longdelay;
    }
         }
      
  
        
   

    
