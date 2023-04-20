/*
 * File:   Main2.c
 * Author: karam
 *
 * Created on April 1, 2023, 7:30 PM
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


char optC[] = "  3)Schedule water ";
char optB[] = "  2)Water When Dry    ";
char optA[] = "   1)Manual Water";
 
char check[] = "0";
int currentADC = 0;

char refillWater[]= "  Refill water";
char fullWater[]= "  Refilled";

char soilDry[] = "D";
char soilMoist[] = "M";

char success[] = "Q";
char random[]="R";

char worked[]="   Worked";

char waterChange[] ="   Water set at";
char highBLE[]="     HIGH";
char medBLE[]="    MEDIUM";
char lowBLE[]="     LOW";

int schedule;
int x =0;


#define HIGH 10
#define MEDIUM 6
#define LOW 3





int main(void) {
    moisturesensor_setup();
    lcd_setup();
    adc_setup();
    int z = configureUSART0();
    
    // Enable PA2 as an output pin.
    PORTA.DIRSET = 0b00000100;
    
    // Enable PA3 as an input pin.
    PORTA.DIRCLR = 0b10000000;
    
    // Enable PF6 as an input pin.
    PORTF.DIRCLR = 0b01000000;
    
    int watervalue = 5;
    int timeval;
    
    
   while(1){
       if((PORTF.IN & 0b01000000)==0){
           watervalue = waterSetting();
           currentADC = 0;
       }
       
       if((USART0.STATUS & 0b10000000) ){
           check[0] = receive();
          if(check[0] == '1'){
             currentADC = 1; 
             x =0;
             clear_lcd();
             lcd_string(optA);
             transmit(success);
             waterMannualBLE(watervalue);
             
          }
           if(check[0] == '2'){
            currentADC = 1; 
            x =0;
            clear_lcd();
            lcd_string(optB);
            transmit(success);
            soilMoistureBLE(watervalue);
          }
           if(check[0] == '3'){
            currentADC = 1; 
            x =0;
            clear_lcd();
            lcd_string(optC);
            transmit(success);
            rtc_setup_BLE(5);
            scheduleBLE(watervalue);
                    
          }
           
          if(check[0] =='4'){
               if(AC0.STATUS & 0b00010000)
                   transmit(soilDry);
               else
                   transmit(soilMoist);
                   
           }
           if(check[0]== 'h'){
               watervalue = HIGH;
               transmit(success);
               clear_lcd();
               lcd_string(waterChange);  
               rtc_setup(1);
               clear_lcd();
               lcd_string(highBLE);
               rtc_setup(1);
               clear_lcd();
               currentADC = 0;
           }
            if(check[0]== 'm'){
               watervalue = MEDIUM;
               transmit(success);
               clear_lcd();
               lcd_string(waterChange);  
               rtc_setup(1);
               clear_lcd();
               lcd_string(medBLE);
               rtc_setup(1);
               clear_lcd();
               currentADC = 0;\
           }
            if(check[0]== 'l'){
               watervalue = LOW;
               transmit(success);
               clear_lcd();
               lcd_string(waterChange);  
               rtc_setup(1);
               clear_lcd();
               lcd_string(lowBLE);
               rtc_setup(1);
               clear_lcd();
               currentADC = 0;
           }
           
              
     }
           
      /*
          if(check[0] == 'o'){
             clear_lcd();
             lcd_string(refillWater);
            while(1){
                transmit(random);
                delay;
                 if((USART0.STATUS & 0b10000000)){
                    check[0] = receive();
                    if(check[0] == 'K'){
                        clear_lcd();
                        lcd_string(fullWater);
                        transmit(random);
                        rtc_setup(5);
                        clear_lcd();
                        break;
                        
                    }
                     
                 }
             } 
          } 
       */            
     
       
     
      if((ADC0.RES <= 409.6) || (currentADC == 0)){
          ADC0.MUXPOS = 0x07; // Select PD7 (AIN2) as the ADC input.
          currentADC =0;
          ADC0.INTFLAGS = 0b00000001;
          if (ADC0.RES >= 2457.6) //option F
        {   
            lcd_string(optC);
            ADC0.INTFLAGS = 0b00000001;
            timeval =rtc_setup_ADC(5);
            if (timeval != 1){
              if(x == 0)
                schedule = schedulingOptions();
              ADC0.MUXPOS = 0x07;
              rtc_setup_ADC(2);
              currentADC =0;
              scheduleADC(watervalue,schedule);
              clear_lcd();
               x++; 
            
           }
          }
       
        
          else if (ADC0.RES >= 1638.4)  //option D
        {  lcd_string(optB);
            x =0;
            ADC0.INTFLAGS = 0b00000001;
            soilMoistureADC(watervalue);
        }
        
        
        
         else if (ADC0.RES >= 819.2) //option B
        {
            x =0;
            lcd_string(optA);
            ADC0.INTFLAGS = 0b00000001;
            waterMannualADC(watervalue);
        }
        
       
        longdelay;
        clear_lcd();
    }
      else
          ADC0.INTFLAGS = 0b00000001;
      
  }
}

    
    
    

    

