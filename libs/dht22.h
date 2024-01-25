#ifndef _DHT22_H_
#define _DHT22_H_

#define MAXTIMINGS 85
static int DHTPIN = 15; 
static int dht22_dat[5] = {0, 0, 0, 0, 0};

void dht22_setup();
uint8_t sizecvt(const int read);
int read_dht22_dat();

#endif
