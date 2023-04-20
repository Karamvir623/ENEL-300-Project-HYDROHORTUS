#ifndef AVR_H_
#define AVR_H_

int configureUSART1();

void microdelay1(unsigned int val);

void millidelay1(unsigned int val);

void transmit1(char*p);

char receive1();

void receiveword1(char*p, int size);

int receiveAOK1();

void sendr1();


#endif 

