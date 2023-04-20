/* 
 * File:   LCDHeader.h
 * Author: tbwhi
 *
 * Created on March 31, 2023, 10:47 AM
 */

#ifndef LCDHEADER_H
#define	LCDHEADER_H


#ifndef delay
#define delay { int __x = 1000; while(--__x); }
#endif

#ifndef longdelay
#define longdelay { int __x = 16000; while(--__x); }
#endif

#ifndef longerdelay
#define longerdelay { int __x = 160000; while(--__x); }
#endif

void lcd_string(char *letter);
void lcd_single(char character);
void lcd_setup();
void adc_setup();
void clear_lcd();

#endif	/* LCDHEADER_H */

