#ifndef DEVICESETTINGS_H
#define	DEVICESETTINGS_H


void watersensor_setupBLE(int watervalue); //setup settings for water sensor
void watersensor_setupADC(int watervalue);
void scheduleBLE(int watervalue);
void scheduleADC(int watervalue, int schedule);
int schedulingOptions();
int timer(int setTime);
void soilMoistureBLE(int watervalue);
void soilMoistureADC(int watervalue);
int waterSetting();



#endif	/* WATERSENSORHEADER_H */
