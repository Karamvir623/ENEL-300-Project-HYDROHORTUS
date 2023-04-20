

#ifndef NRF24_H_
#define NRF24_H_
int configureUSART0();
void microdelay(unsigned int val);

void millidelay(unsigned int val);

void transmit(char*p);

char receive();

void receiveword(char*p, int size);

int receiveAOK();

void sendr();


#endif 